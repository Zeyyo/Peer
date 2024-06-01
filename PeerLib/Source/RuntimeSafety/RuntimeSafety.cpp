#include "PEer_pch.h"
#include <thread>
#include "ServiceManager/ServiceTable.h"
#include "NetworkFilterManager/FilterTable.h"
#include "config.h"
#include "RuntimeSafety.h"

namespace RuntimeSafety
{
	void SanitizeServices()
	{
		ServiceManager::RegisterServices();
		for (;;)
		{
			ServiceManager::ServiceTable::Instance().StopAll();
			std::this_thread::sleep_for(
				std::chrono::milliseconds(
					SERVICE_SANITIZATION_LOOP_ITERATION_HOLD_TIME_MS));
		}
	}

	void SanitizeNetwork()
	{
		NetworkFilterManager::RegisterFilters();
		NetworkFilterManager::FilterTable::Instance().AddAll();
	}
}