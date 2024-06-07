#pragma once

#include <string>
#include <exception>
#include "Types/Task.h"

namespace Exceptions::TaskManagerExceptions
{
    class TaskNotRegisteredException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        TaskNotRegisteredException(const Types::TASKID error) : szErrorMessage("Command not registered: " + std::to_string(error)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };
}