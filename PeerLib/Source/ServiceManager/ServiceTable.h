#pragma once
#include <functional>
#include "IService.h"

namespace ServiceManager
{
    void RegisterServices();

    class ServiceTable
    {
    public:
        using ServiceCreator = std::function<std::unique_ptr<IService>()>;

        static ServiceTable& Instance() {
            static ServiceTable instance;
            return instance;
        }

        void RegisterService(const int pattern, ServiceCreator creator) {
            creators_[pattern] = std::move(creator);
        }

        std::unique_ptr<IService> ServiceLookup(const int pattern) const {
            auto it = creators_.find(pattern);
            if (it != creators_.end()) {
                return it->second();
            }
            return nullptr;
        }

        void StopAll()
        {
            for (auto itService = creators_.begin(); itService != creators_.end(); itService++)
            {
                itService->second()->Stop();
            }
        }

    private:
        ServiceTable() = default;
        std::unordered_map<INT8, ServiceCreator> creators_;
    };
}

