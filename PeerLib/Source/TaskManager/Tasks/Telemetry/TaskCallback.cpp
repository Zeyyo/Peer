#include "PEer_pch.h"
#include "TaskCallback.h"

namespace TaskManager::Tasks::Telemetry
{
	void TaskCallback(Types::SessionData&)
	{
		std::cout << "TaskCallback";
	}
}