#pragma once
#include <fwptypes.h> 
#include <fwpmu.h>
#pragma comment(lib, "fwpuclnt.lib")
#include "IFilter.h"

namespace NetworkFilterManager::Callbacks
{
    void FwpmFilterDeleteCallback0(void* context, const FWPM_FILTER_CHANGE0* change)
    {
        IFilter* iFilter = reinterpret_cast<IFilter*>(context);
        iFilter->AddFilter();
    }
}