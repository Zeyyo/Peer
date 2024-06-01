#include "PEer_pch.h"


#include "Filters.h"

namespace NetworkFilterManager::Filters
{
	AvastFilter::AvastFilter(std::string szAddress, HANDLE hEngine, GUID FILTER_KEY)
	{
		szAddress_ = szAddress;
		hEngine_ = hEngine;
		FILTER_KEY_ = FILTER_KEY;
	};
}