#include "PEer_pch.h"
#include <codecvt>
#include <locale>

#include "StrToWStr.h"

namespace Utilities::Converters
{
    std::wstring StrToWStr(const std::string& stringToConvert)
    {
        int sizeNeeded = MultiByteToWideChar(
            CP_UTF8, 
            0,
            stringToConvert.c_str(),
            (int)stringToConvert.size(),
            NULL, 
            0);
        std::wstring wstrTo(sizeNeeded, 0);
        MultiByteToWideChar(
            CP_UTF8,
            0, 
            stringToConvert.c_str(),
            (int)stringToConvert.size(),
            &wstrTo[0], 
            sizeNeeded);
        return wstrTo;
    }
}