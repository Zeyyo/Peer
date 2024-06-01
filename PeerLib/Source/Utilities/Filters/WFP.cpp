#include "PEer_pch.h"

#include "WFP.h"

namespace Utilities::Filters
{
	HANDLE FetchWFPEngine()
	{
		HANDLE engineHandle = NULL;
		DWORD result = FwpmEngineOpen0(NULL, RPC_C_AUTHN_WINNT, NULL, NULL, &engineHandle);
		if (result != ERROR_SUCCESS) {
			throw Exceptions::NetworkFilterManagerExceptions::WFPEngineHandleFetchException(result);
		}
		return engineHandle;
	}

	bool FilterExists(HANDLE engineHandle, GUID& key, FWPM_FILTER0& filter)
	{
		DWORD deResult = FwpmFilterGetByKey0(engineHandle, &key, (FWPM_FILTER0**)&filter);
		if (deResult == FWP_E_FILTER_NOT_FOUND)
		{
			return false;
		}
		return true;
	}
}