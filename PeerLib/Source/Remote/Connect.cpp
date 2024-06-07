#include "PEer_pch.h"
#include "Utilities/SocketOperations/SocketOperations.h"
#include "Events/Exceptions/SocketOperationExceptions.h"
#include "Events/Exceptions/NetworkOperationExceptions.h"
#include "Events/Logger/OstreamLogger.h"
#include "Helpers/ConnectionHelper/ConnectionHelper.h"
#include "config.h"
#include "ConnectionManager/SessionHandling/Session/Session.h"
#include "Types/Session.h"
#include "Connect.h"

namespace Remote
{
	WORD AttemptRemoteCall(
		std::unique_ptr<PeerLibrary::Session>&& pSession,
		std::string szAddress, 
		Types::PORT port)
	{
		SOCKET socket;

		sockaddr_in hint;
		hint.sin_family = AF_INET;
		hint.sin_port = htons(port);
		inet_pton(AF_INET, szAddress.c_str(), &hint.sin_addr);
		int addrSize = sizeof(hint);

		try
		{
			socket = Utilities::SocketOperations::GetSocket();
		}
		catch (Exceptions::SocketOperationExceptions::SocketCreationException& e)
		{
			std::string szErrorMessage = e.GetError();
			Logger::LOG[Logger::Level::Error] << szErrorMessage << " Exception thrown at GetSocket()" << Logger::endl;
			return -0x1;
		}



		bool Success = Helpers::OperationHelper<
			Exceptions::SocketOperationExceptions::ConnectException>::
			AttemptOperation(
				MAX_CONNECTION_ATTEMPTS,
				CONNECTION_ATTEMPT_TIMEOUT,
				CONNECTION_TIMEOUT,
				Utilities::SocketOperations::Connect,
				socket,
				(sockaddr&)hint,
				addrSize,
				[](Exceptions::SocketOperationExceptions::ConnectException) {});
		if (Success == false)
			throw Exceptions::NetworkOperationExceptions::HostUnreachableException(szAddress);

		pSession->socket_ = socket;
	}
}