#pragma once
#include <functional>
#include "IFilter.h"
#include "config.h"

namespace NetworkFilterManager
{
    void RegisterFilters();

    class FilterTable
    {
    public:
        using FilterCreator = std::function<std::unique_ptr<IFilter>()>;

        static FilterTable& Instance() {
            static FilterTable instance;
            return instance;
        }

        void RegisterFilter(const int pattern, FilterCreator creator) {
            creators_[pattern] = std::move(creator);
        }

        std::unique_ptr<IFilter> FilterCreatorLookup(const int pattern) const {
            auto it = creators_.find(pattern);
            if (it != creators_.end()) {
                return it->second();
            }
            return nullptr;
        }

        std::unique_ptr<IFilter> FilterLookup(const int pattern) {
            auto it = filters_.find(pattern);
            if (it != filters_.end()) {
                return std::move(it->second);
            }
            return nullptr;
        }

        void AddAll()
        {
            for (auto itFilter = creators_.begin(); itFilter != creators_.end(); itFilter++)
            {
                std::unique_ptr<IFilter> iFilter = itFilter->second();
                WORD bSuccess = iFilter->AddFilter();
                if (bSuccess == FILTER_ERROR) { continue; }
                iFilter->KeepAlive();
                filters_[itFilter->first] = std::move(iFilter);
            }
        }

        void RemoveAll()
        {
            for (auto itFilter = creators_.begin(); itFilter != creators_.end(); itFilter++)
            {
                itFilter->second()->RemoveFilter();
            }
        }

    private:
        FilterTable() = default;
        std::unordered_map<INT8, FilterCreator> creators_;
        std::unordered_map<INT8, std::unique_ptr<IFilter>> filters_;
    };
}