#include "PEer_pch.h"
#include <sstream>
#include "DecToHexStr.h"

namespace Utilities::Converters
{
    std::string DecimalToHexadecimalString(int decimal) 
    {
        std::stringstream stream;
        stream << std::hex << decimal;
        return stream.str();
    }
}