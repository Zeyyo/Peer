#pragma once

namespace TaskManager
{
	static class ITask
	{
	public:
		virtual void Run() = 0;
	};
}