#include "PEer_pch.h"

#include <thread>
#include "ServiceManager/ServiceTable.h"
#include "Initialize.h"
#include "InitializeThreads.h"
#include "RuntimeSafety/RuntimeSafety.h"

#include "TaskManager/TaskManager.h"
#include "TaskManager/config.h"

namespace Entry
{
	void Initialize()
	{
		TaskManager::Initialize();
		//TaskManager::Do(DEFAULT);
		//TaskManager::Do(NETWORK_SANITIZATION);
		TaskManager::Do(STARTUP_TELEMETRY);
	}
}