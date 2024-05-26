#include "PEer_pch.h"
#include "ServiceTable.h"
#include "Services/Services.h"
#include "config.h"

#include "Utilities/Service/OpenSCManager.h"

namespace ServiceManager
{
    void RegisterServices()
    {
        SC_HANDLE schSCManager = Utilities::Service::FetchSCManager();
        std::cout << "sdf";

#pragma region AVAST_SVCs
        //ServiceTable::Instance().RegisterService(
        //    AVAST_AV,
        //    [schSCManager]() { return std::make_unique<Services::AvastAV>(cexprAvastAV,schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_ANTI_TRACK_SVC,
        //    [schSCManager]() { return std::make_unique<Services::AvastAntiTrackSvc>(cexprAvastAntiTrackSvc, schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_CLEANUP_SVC,
        //    [schSCManager]() { return std::make_unique<Services::CleanupPSvc>(cexprAvastCleanupPSvc, schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_DRIVER_UPD_SVC,
        //    [schSCManager]() { return std::make_unique<Services::DriverUpdSvc>(cexprAvastDriverUpdSvc, schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_FIREWALL,
        //    [schSCManager]() { return std::make_unique<Services::AvastFirewall>(cexprAvastFirewall, schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_TOOLS,
        //    [schSCManager]() { return std::make_unique<Services::AvastTools>(cexprAvastTools, schSCManager); });
        //ServiceTable::Instance().RegisterService(
        //    AVAST_WSC_REPORTER,
        //    [schSCManager]() { return std::make_unique<Services::AvastWscReporter>(cexprAvastWscReporter, schSCManager); });
#pragma endregion AVAST_SVCs

#pragma region GOOGLE_SVCs
        ServiceTable::Instance().RegisterService(
            GOOGLE_UPDATER_INTERNAL_SVC,
            [schSCManager]() { return std::make_unique<Services::GoogleUpdaterInternalService>(cexprGoogleUpdaterInternalService, schSCManager); });
        ServiceTable::Instance().RegisterService(
            GOOGLE_UPDATER_SVC,
            [schSCManager]() { return std::make_unique<Services::GoogleUpdaterService>(cexprGoogleUpdaterService, schSCManager); });
#pragma endregion GOOGLE_SVCs

#pragma region MOZILLA_SVCs
        ServiceTable::Instance().RegisterService(
            MOZILLA_MAINTENANCE_SVC,
            [schSCManager]() { return std::make_unique<Services::MozillaMaintenance>(cexprMozillaMaintenance, schSCManager); });
#pragma endregion MOZILLA_SVCs

    }
}