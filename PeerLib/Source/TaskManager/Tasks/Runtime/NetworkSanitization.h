#pragma once
#include "TaskManager/ITask.h"
#include "RuntimeSafety/RuntimeSafety.h"

namespace TaskManager::Tasks::Runtime
{
	static class NetworkSanitization : public ITask
	{
	public:
		void Run()
		{
			std::thread NetworkSanitization(RuntimeSafety::SanitizeNetwork);
			if (NetworkSanitization.joinable())
			{
				NetworkSanitization.detach();
			}
		}
	};
}