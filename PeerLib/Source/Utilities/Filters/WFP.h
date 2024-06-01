#pragma once
#include <fwptypes.h>
#include <fwpmu.h>
#pragma comment(lib, "fwpuclnt.lib")

#include "Events/Exceptions/NetworkFilterManagerExceptions.h"

namespace Utilities::Filters
{
	HANDLE FetchWFPEngine();
    template<typename T>
    void AddNetwFilter(T UID, HANDLE hEngine, FWPM_FILTER0& filter)
	{
		DWORD result = FwpmFilterAdd0(hEngine, &filter, NULL, NULL);
		if (result != ERROR_SUCCESS) {
			throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException(UID);
		}
	}
    bool FilterExists(HANDLE engineHandle, GUID& key, FWPM_FILTER0& filter);
}