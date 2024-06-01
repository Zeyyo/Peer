#pragma once
#include "NetworkFilterManager/IFilter.h"

namespace NetworkFilterManager::Filters
{
	class AvastFilter : public IAddressFilter
	{
	public:
		AvastFilter(std::string szAddress, HANDLE hEngine, GUID FILTER_KEY);
	};

}