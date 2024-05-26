#pragma once

namespace ServiceManager::Services
{
#pragma region AVAST_AV
	class AvastAV : public IService
	{
	public:
		AvastAV(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class AvastAntiTrackSvc : public IService
	{
	public:
		AvastAntiTrackSvc(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class CleanupPSvc : public IService
	{
	public:
		CleanupPSvc(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class DriverUpdSvc : public IService
	{
	public:
		DriverUpdSvc(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class AvastFirewall : public IService
	{
	public:
		AvastFirewall(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class AvastTools : public IService
	{
	public:
		AvastTools(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class AvastWscReporter : public IService
	{
	public:
		AvastWscReporter(std::string szServiceName, SC_HANDLE hSCManager);
	};
#pragma endregion AVAST_AV

#pragma region GOOGLE
	class GoogleUpdaterInternalService : public IService
	{
	public:
		GoogleUpdaterInternalService(std::string szServiceName, SC_HANDLE hSCManager);
	};

	class GoogleUpdaterService : public IService
	{
	public:
		GoogleUpdaterService(std::string szServiceName, SC_HANDLE hSCManager);
	};
#pragma endregion GOOGLE

#pragma region MOZILLA
	class MozillaMaintenance : public IService
	{
	public:
		MozillaMaintenance(std::string szServiceName, SC_HANDLE hSCManager);
	};
#pragma endregion MOZILLA

}