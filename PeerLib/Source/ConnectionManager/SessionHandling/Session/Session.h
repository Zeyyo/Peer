#pragma once
#include "Types/Session.h"

namespace PeerLibrary
{
	class Session
	{
	public:
		Session(void(*fnRequestTask)(Types::SessionData&)) : fnmRequestTask(fnRequestTask)
		{}
		std::string szIpAdress_;
		SOCKET socket_ = NULL;
		sockaddr pAddr_;
		int addrSize_ = sizeof(pAddr_);
		void(*fnmRequestTask)(Types::SessionData&);
		Types::SessionData GetSessionData() const;
		void Close();
	};
}