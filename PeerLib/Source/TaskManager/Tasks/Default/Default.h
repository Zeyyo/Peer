#pragma once
#include "TaskManager/ITask.h"

namespace TaskManager::Tasks::Default
{
	static class Default : public ITask
	{
	public:
		void Run();
	};
}