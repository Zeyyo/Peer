#pragma once
#include "TaskManager/ITask.h"
#include "Types/Networking.h"
#include "Types/Session.h"
#include "ConnectionManager/SessionHandling/Session/Session.h"
#include "ConnectionManager/Core/Core.h"


namespace TaskManager::Tasks::Telemetry
{
	static class Startup : public ITask
	{
	public:
		Startup(std::string szAddress, Types::PORT port);
		void Run();
	private:
		std::unique_ptr<PeerLibrary::Session> pSession_;
		std::string szAddress_;
		Types::PORT port_;

		PeerLibrary::Core core_;
	};

}