#pragma once
#include <string>
#include <Windows.h>

namespace Exceptions::NetworkFilterManagerExceptions
{
    class WFPEngineHandleFetchException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WFPEngineHandleFetchException(const DWORD message) :
            szErrorMessage("Could not retreive WFP engine handle " + std::to_string(message)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class WFPNetworkFilterAddException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WFPNetworkFilterAddException(const std::string& address) :
            szErrorMessage("Could not add WFP filter for " + address) {}

        WFPNetworkFilterAddException(const unsigned short& port) :
            szErrorMessage("Could not add WFP filter for port " + std::to_string(port)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class WFPNetworkFilterRemoveException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WFPNetworkFilterRemoveException(const std::string& address) :
            szErrorMessage("Could not remove WFP filter for " + address) {}

        WFPNetworkFilterRemoveException(const unsigned short& port) :
            szErrorMessage("Could not remove WFP filter for port " + std::to_string(port)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

    class WFPNetworkFilterSubscriptionException : public std::exception {
    private:
        std::string szErrorMessage;
    public:
        WFPNetworkFilterSubscriptionException(const std::string& address) :
            szErrorMessage("Could not subscribe to WFP filter events for " + address) {}

        WFPNetworkFilterSubscriptionException(const unsigned short& port) :
            szErrorMessage("Could not subscribe to WFP filter events for port " + std::to_string(port)) {}

        const char* what() const noexcept override {
            return szErrorMessage.c_str();
        }
        std::string GetError() const
        {
            return szErrorMessage;
        }
    };

}