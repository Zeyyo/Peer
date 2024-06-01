#pragma once

#include <fwptypes.h>
#include <fwpmu.h>
#pragma comment(lib, "fwpuclnt.lib")

#include "Types/Networking.h"

namespace NetworkFilterManager
{
	class IFilter
	{
	public:
		virtual void AddFilter() = 0;
		virtual void RemoveFilter() = 0;

	protected:
		GUID FILTER_KEY_;
		HANDLE hEngine_ = NULL;

		FWPM_FILTER0 filter_ = { 0 };
		FWPM_FILTER_CONDITION0 condition_ = { 0 };

	};

	class IPortFilter : public IFilter
	{
	public:
		void AddFilter() override;
		void RemoveFilter() override;

	protected:
		Types::PORT port_;
	};

	class IAddressFilter : public IFilter
	{
	public:
		void AddFilter() override;
		void RemoveFilter() override;

	protected:
		std::string szAddress_;
	};

}
