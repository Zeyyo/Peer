#include "PEer_pch.h"
#include "ConnectionManager/SessionHandling/Session/Session.h"
#include "Remote/Connect.h"
#include "config.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"
#include "Events/Logger/OstreamLogger.h"
#include "SessionOperator.h"

namespace PeerLibrary
{
	std::unique_ptr<Session> ObtainSession(void(*fnTask)(Types::SessionData&), std::string szAddress, Types::PORT taskPort)
	{
		auto session = std::make_unique<Session>(fnTask);
		try
		{
			WORD res = Remote::AttemptRemoteCall(std::move(session), szAddress, taskPort);
			if (res == -1) 
				return nullptr;
		}
		catch (Exceptions::NetworkOperationExceptions::HostUnreachableException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at AttemptRemoteCall()" << Logger::endl;
			return nullptr;
		}
		return session;
	}
}