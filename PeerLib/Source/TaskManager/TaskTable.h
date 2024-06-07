#pragma once
#include <functional>
#include "Types/Task.h"
#include "ITask.h"
#include "config.h"
#include "Events/Exceptions/TaskManagerExceptions.h"

namespace TaskManager
{
    void RegisterTasks();

    static class TaskTable
    {
    public:
        using Task = std::function< std::unique_ptr<ITask>()>;

        static TaskTable& Instance() {
            static TaskTable instance;
            return instance;
        }

        void RegisterTask(Types::TASKID pattern, Task creator) {
            Tasks_[pattern] = std::move(creator);
        }

        static std::unique_ptr<ITask> TaskLookup(Types::TASKID pattern) {
            auto it = Tasks_.find(pattern);
            if (it != Tasks_.end()) {
                return it->second();
            }
            throw Exceptions::TaskManagerExceptions::TaskNotRegisteredException(pattern);
        }

    private:
        TaskTable() = default;
        static std::unordered_map<Types::TASKID, Task> Tasks_;
    };
}