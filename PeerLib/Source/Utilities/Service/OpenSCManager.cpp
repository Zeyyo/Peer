#include "PEer_pch.h"
#include "OpenSCManager.h"

namespace Utilities::Service
{
	SC_HANDLE FetchSCManager()
	{
		SC_HANDLE schSCManager = OpenSCManager(
			nullptr,
			nullptr,
			SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			std::cout << " " << GetLastError() << "\n";
		}
		return schSCManager;
	}
}