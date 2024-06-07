#pragma once
#include "Types/Networking.h"

namespace Remote
{
	WORD AttemptRemoteCall(
		std::unique_ptr<PeerLibrary::Session>&& pClientSession,
		std::string szAddress,
		Types::PORT port);
}

