#include "PEer_pch.h"

#include <chrono>

#include "GetWaitTime.h"

namespace Utilities::Service
{
	std::chrono::milliseconds GetWaitTime(DWORD const dwWaitHint)
	{
		auto waitTime = dwWaitHint / 10;

		if (waitTime < 1000)
			waitTime = 1000;
		else if (waitTime > 3000)
			waitTime = 3000;

		return std::chrono::milliseconds(waitTime);
	}
}