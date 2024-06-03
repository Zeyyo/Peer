#include "PEer_pch.h"
#include "Filters/Filters.h"
#include "config.h"

#include "Utilities/Filters/WFP.h"

#include "FilterTable.h"

namespace NetworkFilterManager
{
    void RegisterFilters()
    {
        HANDLE engineHandle = Utilities::Filters::FetchWFPEngine();

        FilterTable::Instance().RegisterFilter(
            AVAST_AV_SERVER,
            [engineHandle]() { return std::make_unique<Filters::AvastFilter>(cexprAvastAVServer, engineHandle, AVAST_SERVER_FILTER_KEY); });

        FilterTable::Instance().RegisterFilter(
            AVAST_AV_APP_SERVER,
            [engineHandle]() { return std::make_unique<Filters::AvastAppFilter>(cexprAvastAppAVServer, engineHandle, AVAST_APP_SERVER_FILTER_KEY); });
    }
}