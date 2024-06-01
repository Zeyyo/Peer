#include "PEer_pch.h"
#include "Events/Exceptions/NetworkFilterManagerExceptions.h"

#include <fwpmu.h>
#pragma comment(lib, "fwpuclnt.lib")

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
}