#include "PEer_pch.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "Events/Exceptions/NetworkFilterManagerExceptions.h"
#include "IFilter.h"

namespace NetworkFilterManager
{
    template<typename T>
    void AddNetwFilter(T UID, HANDLE hEngine, FWPM_FILTER0& filter)
    {
        DWORD result = FwpmFilterAdd0(hEngine, &filter, NULL, NULL);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException(UID);
        }
    }

	void IPortFilter::AddFilter()
	{
        filter_.filterKey = FILTER_KEY_;
        filter_.layerKey = FWPM_LAYER_OUTBOUND_TRANSPORT_V4;
        filter_.displayData.name = (wchar_t*)L"WinNEtw-PortFilter";
        filter_.action.type = FWP_ACTION_BLOCK;
        filter_.filterCondition = &condition_;
        filter_.numFilterConditions = 1;
        filter_.subLayerKey = FWPM_SUBLAYER_UNIVERSAL;
        filter_.weight.type = FWP_EMPTY;

        condition_.fieldKey = FWPM_CONDITION_IP_REMOTE_PORT;
        condition_.matchType = FWP_MATCH_EQUAL;
        condition_.conditionValue.type = FWP_UINT16;
        condition_.conditionValue.uint16 = port_;

        try
        {
            AddNetwFilter(port_, hEngine_, filter_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException& e)
        {
            std::cout << e.GetError();
        }
	}

    void IPortFilter::RemoveFilter()
    {
        DWORD result = FwpmFilterDeleteByKey0(hEngine_, &FILTER_KEY_);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterRemoveException(port_);
        }
    }

    void IAddressFilter::AddFilter()
    {
        filter_.layerKey = FWPM_LAYER_OUTBOUND_TRANSPORT_V4;
        filter_.filterKey = FILTER_KEY_;
        filter_.displayData.name = (wchar_t*)L"WinNEtw-AddressFilter";
        filter_.action.type = FWP_ACTION_BLOCK;
        filter_.filterCondition = &condition_;
        filter_.numFilterConditions = 1;
        filter_.subLayerKey = FWPM_SUBLAYER_UNIVERSAL;
        filter_.weight.type = FWP_EMPTY;

        sockaddr_in addr = { 0 };
        inet_pton(AF_INET, szAddress_.c_str(), &addr.sin_addr);
        UINT32 u32Address = ntohl(addr.sin_addr.s_addr);
        std::cout << WSAGetLastError();
        condition_.fieldKey = FWPM_CONDITION_IP_REMOTE_ADDRESS;
        condition_.matchType = FWP_MATCH_EQUAL;
        condition_.conditionValue.type = FWP_UINT32;
        condition_.conditionValue.uint32 = u32Address;

        try
        {
            AddNetwFilter(szAddress_, hEngine_, filter_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException& e)
        {
            std::cout << e.GetError();
        }
    }

    void IAddressFilter::RemoveFilter()
    {
        DWORD result = FwpmFilterDeleteByKey0(hEngine_, &FILTER_KEY_);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterRemoveException(szAddress_);
        }
    }

}