#include "PEer_pch.h"

#include <vector>
#include <thread>

#include "IService.h"
#include "Events/Exceptions/ServiceManagerExceptions.h"
#include "Utilities/Service/GetWaitTime.h"

namespace ServiceManager
{
	SC_HANDLE IService::FetchServiceHandle(SC_HANDLE schSCManager)
	{
		std::wstring wstr(szServiceName_.begin(), szServiceName_.end());
		LPCWSTR lpctstrServiceName = wstr.c_str();

		SC_HANDLE schService = ::OpenService(
			schSCManager,
			lpctstrServiceName,
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
			throw Exceptions::ServiceManagerExceptions::ServiceHandleException(szServiceName_);
		return schService;
	}

	void IService::UpdateServiceStatus()
	{
		BOOL bError = QueryServiceStatusEx(
			hService_,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&lpBuffer_,
			dwBufSize_,
			&dwBytesNeeded_);

		if (bError == 0)
			throw Exceptions::ServiceManagerExceptions::ServiceStatusQueryException(szServiceName_);
	}

	bool IService::IsServiceRunning()
	{
		UpdateServiceStatus();
		if (lpBuffer_.dwCurrentState == SERVICE_STOPPED)
			return false;
		return true;
	}

	bool IService::IsDependentServiceRunning(_SERVICE_STATUS_PROCESS& serviceStatusProcess)
	{
		if (serviceStatusProcess.dwCurrentState == SERVICE_STOPPED)
			return false;
		return true;
	}

	bool IService::IsStopPending()
	{
		UpdateServiceStatus();
		if (lpBuffer_.dwCurrentState == SERVICE_STOP_PENDING)
			return true;
		return false;
	}

	void IService::AwaitPendingStop(std::chrono::high_resolution_clock::time_point startTime)
	{
		while (IsStopPending())
		{
			msWaitTime_ = Utilities::Service::GetWaitTime(lpBuffer_.dwWaitHint);
			std::this_thread::sleep_for(msWaitTime_);

			if (std::chrono::high_resolution_clock::now() - startTime > msTimeout_)
				throw Exceptions::ServiceManagerExceptions::ServiceStopTimeoutException(szServiceName_);
		}
	}

	void IService::AwaitDependentServicePendingStop(std::chrono::high_resolution_clock::time_point startTime, _SERVICE_STATUS_PROCESS& serviceSatusProcess)
	{
		while (IsDependentServiceRunning(serviceSatusProcess))
		{
			std::chrono::milliseconds waitTime = Utilities::Service::GetWaitTime(serviceSatusProcess.dwWaitHint);
			std::this_thread::sleep_for(waitTime);

			if (std::chrono::high_resolution_clock::now() - startTime > msTimeout_)
				throw Exceptions::ServiceManagerExceptions::DependentServiceStopTimeoutException(szServiceName_);
		}
	}

	bool IService::StopDependentService(SC_HANDLE schService, SERVICE_STATUS_PROCESS& serviceStatusProcess)
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		BOOL bError = ControlService(schService, SERVICE_CONTROL_STOP, reinterpret_cast<LPSERVICE_STATUS>(&serviceStatusProcess));
		if (bError != 0)
		{
			throw Exceptions::ServiceManagerExceptions::DependentServiceStopException(szServiceName_, bError);
			std::cout << bError;
		}
		AwaitDependentServicePendingStop(startTime, serviceStatusProcess);
	}

	bool IService::StopDependentServices()
	{
		auto bytesNeeded = DWORD{ 0 };
		auto count = DWORD{ 0 };

		if (!::EnumDependentServices(
			hService_,
			SERVICE_ACTIVE,
			nullptr,
			0,
			&bytesNeeded,
			&count))
		{
			DWORD erro = GetLastError();
			if (erro != ERROR_MORE_DATA)
				return false;

			std::vector<unsigned char> buffer(bytesNeeded, 0);

			if (!::EnumDependentServices(
				hService_,
				SERVICE_ACTIVE,
				reinterpret_cast<LPENUM_SERVICE_STATUS>(buffer.data()),
				bytesNeeded,
				&bytesNeeded,
				&count))
			{
				return false;
			}

			for (auto i = DWORD{ 0 }; i < count; ++i)
			{
				auto enumServiceStatus = static_cast<ENUM_SERVICE_STATUS>
					(*(reinterpret_cast<LPENUM_SERVICE_STATUS>(buffer.data() + i)));

				SC_HANDLE handle = ::OpenService(
					hSCManager_,
					enumServiceStatus.lpServiceName,
					SERVICE_STOP | SERVICE_QUERY_STATUS);

				if (!handle)
					return false;

				auto ssp = SERVICE_STATUS_PROCESS{ 0 };

				try
				{
					StopDependentService(handle, ssp);
				}
				catch (const Exceptions::ServiceManagerExceptions::DependentServiceStopException& e)
				{
					std::string szErrorMessage = e.GetError();
					std::cerr << szErrorMessage;
					return false;
				}
				catch (const Exceptions::ServiceManagerExceptions::DependentServiceStopTimeoutException& e)
				{
					std::string szErrorMessage = e.GetError();
					std::cerr << szErrorMessage;
					return false;
				}
			}
		}
		return true;
	}

	void IService::Refresh(SC_HANDLE schSCManager)
	{
		try
		{
			hService_ = FetchServiceHandle(schSCManager);
			hSCManager_ = schSCManager;
			UpdateServiceStatus();
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			hService_ = NULL;
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceStatusQueryException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	void IService::Stop()
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		bool bIsServiceRunning;
		bool bIsServiceStopPending;
		try
		{
			bIsServiceRunning = IsServiceRunning();
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceStatusQueryException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
			return;
		}

		if (!bIsServiceRunning)
		{
			//std::cout << "\nDunzoo ! ! ! " << szServiceName_ << "\n";
			return;
		}
		
		try
		{
			bIsServiceStopPending = IsStopPending();
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceStatusQueryException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
			return;
		}

		if (bIsServiceStopPending)
		{
			try
			{
				AwaitPendingStop(startTime);
			}
			catch (const Exceptions::ServiceManagerExceptions::ServiceStopTimeoutException& e)
			{
				std::string szErrorMessage = e.GetError();
				std::cerr << szErrorMessage;
				return;
			}
		}

		bool bIsDependentServicesStopped = StopDependentServices();
		if (!bIsDependentServicesStopped)
			return;

		BOOL bError = ControlService(hService_, SERVICE_CONTROL_STOP, &serviceStatus_);
		if (bError == 0)
		{
			std::cout << "\n" << GetLastError() << "\n";
		}
		
	}
}