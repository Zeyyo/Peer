#include "PEer_pch.h"

#include "config.h"
#include "Tasks/Default/Default.h"
#include "TaskTable.h"
#include "Tasks/Runtime/NetworkSanitization.h"
#include "Tasks/Runtime/ServiceSanitization.h"
#include "Tasks/Default/Default.h"
#include "Tasks/Telemetry/Startup.h"
#include "Tasks/Telemetry/config.h"

namespace TaskManager
{
    std::unordered_map<Types::TASKID, TaskTable::Task> TaskTable::Tasks_;

    void RegisterTasks()
    {
        TaskTable::Instance().RegisterTask(
            DEFAULT,
            []() { return std::make_unique<Tasks::Default::Default>(); });
#pragma region RUNTIME
        TaskTable::Instance().RegisterTask(
            NETWORK_SANITIZATION,
            []() { return std::make_unique<Tasks::Runtime::NetworkSanitization>(); });

        TaskTable::Instance().RegisterTask(
            SERVICE_SANITIZATIO,
            []() { return std::make_unique<Tasks::Runtime::ServiceSanitization>(); });
#pragma endregion RUNTIME

        TaskTable::Instance().RegisterTask(
            STARTUP_TELEMETRY,
            []() { return std::make_unique<Tasks::Telemetry::Startup>(cexprAddress, PORT); });
    }
}