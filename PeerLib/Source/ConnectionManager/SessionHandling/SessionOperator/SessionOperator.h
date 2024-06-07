#pragma once
#include "Types/Networking.h"
#include "Types/Session.h"
#include "ConnectionManager/SessionHandling/Session/Session.h"

namespace PeerLibrary
{
	std::unique_ptr<Session> ObtainSession(void(*fnTask)(Types::SessionData&), std::string szAddress, Types::PORT taskPort);
}