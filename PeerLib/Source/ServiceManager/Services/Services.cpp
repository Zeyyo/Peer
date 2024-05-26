#include "PEer_pch.h"

#include "ServiceManager/IService.h"
#include "Events/Exceptions/ServiceManagerExceptions.h"
#include "Services.h"

namespace ServiceManager::Services
{
#pragma region AVAST_AV
	AvastAV::AvastAV(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	AvastAntiTrackSvc::AvastAntiTrackSvc(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	CleanupPSvc::CleanupPSvc(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	DriverUpdSvc::DriverUpdSvc(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	AvastFirewall::AvastFirewall(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	AvastTools::AvastTools(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	AvastWscReporter::AvastWscReporter(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}
#pragma endregion AVAST_AV

#pragma region GOOGLE
	GoogleUpdaterInternalService::GoogleUpdaterInternalService(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}

	GoogleUpdaterService::GoogleUpdaterService(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}
#pragma endregion GOOGLE

#pragma region MOZILLA
	MozillaMaintenance::MozillaMaintenance(std::string szServiceName, SC_HANDLE hSCManager)
	{
		szServiceName_ = szServiceName;
		try
		{
			hSCManager_ = hSCManager;
			hService_ = FetchServiceHandle(hSCManager);
		}
		catch (const Exceptions::ServiceManagerExceptions::ServiceHandleException& e)
		{
			std::string szErrorMessage = e.GetError();
			std::cerr << szErrorMessage;
		}
	}
#pragma endregion MOZILLA

}