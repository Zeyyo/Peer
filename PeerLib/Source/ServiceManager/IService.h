#pragma once
#include <chrono>

namespace ServiceManager
{
	class IService
	{
	public:
		SC_HANDLE FetchServiceHandle(SC_HANDLE schSCManager);

		void UpdateServiceStatus();

		bool IsServiceRunning();
		bool IsDependentServiceRunning(_SERVICE_STATUS_PROCESS& serviceStatusProcess);
		bool IsStopPending();

		void AwaitPendingStop(std::chrono::high_resolution_clock::time_point startTime);
		void AwaitDependentServicePendingStop(std::chrono::high_resolution_clock::time_point startTime, _SERVICE_STATUS_PROCESS& serviceSatusProcess);

		bool StopDependentService(SC_HANDLE schService, SERVICE_STATUS_PROCESS& serviceStatusProces);
		bool StopDependentServices();

		void Refresh(SC_HANDLE hSCManager);
		void Stop();

	protected:
		SC_HANDLE hSCManager_;
		std::string szServiceName_;
		SC_HANDLE hService_ = NULL;
		_SERVICE_STATUS serviceStatus_;
		_SERVICE_STATUS_PROCESS lpBuffer_ = _SERVICE_STATUS_PROCESS{ 0 };
		DWORD dwBufSize_ = sizeof(lpBuffer_);
		DWORD dwBytesNeeded_;

		std::chrono::milliseconds msWaitTime_;
		std::chrono::milliseconds const msTimeout_ = std::chrono::milliseconds(30000);
	};
}