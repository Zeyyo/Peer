#pragma once
#include "Types/Time.h"
#include "Types/Filters.h"

namespace Utilities::NameMangling
{
	using Types::TimeFormat;
	void SuffixMangle(std::string& szBody);
	void PeerPlaceholderSuffixMangle(std::string& szBody);
}