#include "PEer_pch.h"

#include "config.h"
#include "TaskTable.h"
#include "TaskManager.h"
#include "Events/Logger/OstreamLogger.h"

namespace TaskManager
{
	void Initialize()
	{
		RegisterTasks();
	}

	void Do(Types::TASKID taskID)
	{
		try
		{
			auto task = TaskTable::TaskLookup(taskID);
			task->Run();
		}
		catch (const Exceptions::TaskManagerExceptions::TaskNotRegisteredException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << "TaskLookup()." << Logger::endl;
		}
	}
}