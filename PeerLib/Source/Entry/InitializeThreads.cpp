#include "PEer_pch.h"

#include <thread>

#include "InitializeThreads.h"
#include "RuntimeSafety/RuntimeSafety.h"

namespace Entry
{
	void InitializeRuntimeThreads()
	{
		//RuntimeSafety::SanitizeServices();
		RuntimeSafety::SanitizeNetwork();
		//std::thread ServiceSanitization();
		// TODO: Telemetry
		// TODO: Payload
		//ServiceSanitization.detach();
	}
}
