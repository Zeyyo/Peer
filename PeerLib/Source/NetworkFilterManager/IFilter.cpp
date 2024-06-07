#include "PEer_pch.h"

#include "config.h"
#include "Events/Exceptions/NetworkFilterManagerExceptions.h"
#include "IFilter.h"
#include "FilterEventCallbacks.h"
#include "Utilities/Filters/WFP.h"
#include "Utilities/Converters/StrToWStr.h"

namespace NetworkFilterManager
{
#pragma region I_PORT_FILTER
    WORD IPortFilter::AddFilter()
	{
        bool bFilterExists = Utilities::Filters::FilterExists(hEngine_, FILTER_KEY_, filter_);
        if (bFilterExists) { return FILTER_ALREADY_EXISTS; }

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
            Utilities::Filters::AddNetwFilter(port_, hEngine_, filter_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException& e)
        {
            std::cout << e.GetError();
            return FILTER_ERROR;
        }
        return FILTER_SUCCESS;
	}

    void IPortFilter::RemoveFilter()
    {
        DWORD result = FwpmFilterDeleteByKey0(hEngine_, &FILTER_KEY_);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterRemoveException(port_);
        }
    }

    void IPortFilter::KeepAlive()
    {
        try
        {
            SubscribeToFilterChanges(port_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterSubscriptionException& e)
        {
            std::cout << e.GetError();
        }
    }
#pragma endregion I_PORT_FILTER

#pragma region I_ADDRESS_FILTER
    WORD IAddressFilter::AddFilter()
    {
        bool bFilterExists = Utilities::Filters::FilterExists(hEngine_, FILTER_KEY_, filter_);
        if (bFilterExists) { return FILTER_ALREADY_EXISTS; }

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

        condition_.fieldKey = FWPM_CONDITION_IP_REMOTE_ADDRESS;
        condition_.matchType = FWP_MATCH_EQUAL;
        condition_.conditionValue.type = FWP_UINT32;
        condition_.conditionValue.uint32 = u32Address;

        try
        {
            Utilities::Filters::AddNetwFilter(szAddress_, hEngine_, filter_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException& e)
        {
            std::cout << e.GetError();
            return FILTER_ERROR;
        }
        return FILTER_SUCCESS;
    }

    void IAddressFilter::RemoveFilter()
    {
        DWORD result = FwpmFilterDeleteByKey0(hEngine_, &FILTER_KEY_);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterRemoveException(szAddress_);
        }
    }

    void IAddressFilter::KeepAlive()
    {
        try
        {
            SubscribeToFilterChanges(szAddress_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterSubscriptionException& e)
        {
            std::cout << e.GetError();
        }
    }
#pragma endregion I_ADDRESS_FILTER

#pragma region I_APPLICATION_FILTER
    WORD IApplicationFilter::AddFilter()
    {
        bool bFilterExists = Utilities::Filters::FilterExists(hEngine_, FILTER_KEY_, filter_);
        if (bFilterExists) { return FILTER_ALREADY_EXISTS; }

        filter_.layerKey = FWPM_LAYER_ALE_AUTH_CONNECT_V4;
        filter_.filterKey = FILTER_KEY_;
        filter_.displayData.name = (wchar_t*)L"WinNEtw-ApplicationFilter";
        filter_.action.type = FWP_ACTION_BLOCK;
        filter_.filterCondition = &condition_;
        filter_.numFilterConditions = 1;
        filter_.subLayerKey = FWPM_SUBLAYER_UNIVERSAL;
        filter_.weight.type = FWP_EMPTY;

        std::wstring wsAppPathWstr = Utilities::Converters::StrToWStr(szPath_);

        FWP_BYTE_BLOB* appId = nullptr;
        DWORD test = FwpmGetAppIdFromFileName(wsAppPathWstr.c_str(), &appId);
        if (test != ERROR_SUCCESS)
        {
            std::cerr << "Failed to get AppId from file name" << std::endl;
            return FILTER_ERROR;
        }

        FWP_CONDITION_VALUE0 conditionValue;
        conditionValue.type = FWP_BYTE_BLOB_TYPE;
        conditionValue.byteBlob = appId;

        condition_.fieldKey = FWPM_CONDITION_ALE_APP_ID;
        condition_.matchType = FWP_MATCH_EQUAL;
        condition_.conditionValue = conditionValue;

        try
        {
            Utilities::Filters::AddNetwFilter(szPath_, hEngine_, filter_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterAddException& e)
        {
            std::cout << e.GetError();
            return FILTER_ERROR;
        }
        return FILTER_SUCCESS;
    }

    void IApplicationFilter::RemoveFilter()
    {
        DWORD result = FwpmFilterDeleteByKey0(hEngine_, &FILTER_KEY_);
        if (result != ERROR_SUCCESS) {
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterRemoveException(szPath_);
        }
    }

    void IApplicationFilter::KeepAlive()
    {
        try
        {
            SubscribeToFilterChanges(szPath_);
        }
        catch (const Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterSubscriptionException& e)
        {
            std::cout << e.GetError();
        }
    }
#pragma endregion I_APPLICATION_FILTER

    template<typename T>
    void IFilter::SubscribeToFilterChanges(T UID)
    {
        HANDLE changeHandle = nullptr;
        FWPM_FILTER_ENUM_TEMPLATE0_ enumTemplate = { 0 };
        enumTemplate.layerKey = filter_.layerKey;
        enumTemplate.enumType = FWP_FILTER_ENUM_FULLY_CONTAINED;
        enumTemplate.flags = FWP_FILTER_ENUM_FLAG_SORTED;
        enumTemplate.providerContextTemplate = NULL;
        enumTemplate.numFilterConditions = 1;
        enumTemplate.filterCondition = filter_.filterCondition;
        enumTemplate.actionMask = FWP_ACTION_BLOCK;

        FWPM_FILTER_SUBSCRIPTION0_ subscription = { 0 };
        subscription.enumTemplate = &enumTemplate;
        subscription.flags = FWPM_SUBSCRIPTION_FLAG_NOTIFY_ON_DELETE;

        DWORD result = FwpmFilterSubscribeChanges0(
            hEngine_,
            &subscription,
            NetworkFilterManager::Callbacks::FwpmFilterDeleteCallback0,
            this,
            &changeHandle
        );

        if (result != ERROR_SUCCESS) {
            //FwpmFilterUnsubscribeChanges0(engineHandle, changeHandle);
            throw Exceptions::NetworkFilterManagerExceptions::WFPNetworkFilterSubscriptionException(UID);
        }
    }
}