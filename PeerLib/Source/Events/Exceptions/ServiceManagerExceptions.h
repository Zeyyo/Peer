#pragma once
#include <string>

namespace Exceptions::ServiceManagerExceptions
{
    class ServiceHandleException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ServiceHandleException(const std::string& message) : 
            szErrorMessage("Could not retreive service handle for " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class ServiceStatusQueryException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ServiceStatusQueryException(const std::string& message) : 
            szErrorMessage("Could not retreive service status for " + message) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class ServiceStopTimeoutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        ServiceStopTimeoutException(const std::string& message) : 
            szErrorMessage("An attempt at stopping service " + message + " timed out") {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class DependentServiceStopTimeoutException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        DependentServiceStopTimeoutException(const std::string& message) : 
            szErrorMessage("An attempt at stopping dependent service of " + message + " timed out") {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class DependentServiceStopException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        DependentServiceStopException(std::string szParentService, const BOOL& errorCode) : 
            szErrorMessage("An attempt at stopping dependent service of " + szParentService + " failed with code " + std::to_string(errorCode)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

}