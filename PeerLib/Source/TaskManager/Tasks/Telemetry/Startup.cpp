#include "PEer_pch.h"
#include "ConnectionManager/SessionHandling/SessionOperator/SessionOperator.h"
#include "TaskCallback.h"
#include "Startup.h"

namespace TaskManager::Tasks::Telemetry
{
	Startup::Startup(std::string szAddress, Types::PORT port)
	{
		szAddress_ = szAddress;
		port_ = port;
	}

	void Startup::Run()
	{
		PeerLibrary::Core core(MAKEWORD(2, 2));
		core_ = core;

		pSession_ = PeerLibrary::ObtainSession(TaskCallback, szAddress_, port_);
		if (pSession_ == nullptr)
			return;

		Types::SessionData sessionData = pSession_->GetSessionData();
		pSession_->fnmRequestTask(sessionData);
		pSession_->Close();
	}
}