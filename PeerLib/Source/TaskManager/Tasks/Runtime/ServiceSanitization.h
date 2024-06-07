#pragma once
#include "TaskManager/ITask.h"
#include "RuntimeSafety/RuntimeSafety.h"

namespace TaskManager::Tasks::Runtime
{
	static class ServiceSanitization : public ITask
	{
	public:
		void Run()
		{
			std::thread ServiceSanitization(RuntimeSafety::SanitizeServices);
			if (ServiceSanitization.joinable())
			{
				ServiceSanitization.detach();
			}
		}
	};

}