#pragma once
#include <memory>
#include <sigc++/signal.h>
#include "ICommand.hpp"

typedef std::unique_ptr<ICommand> ICommandPtr;

struct IHistory
{
	typedef sigc::signal<void()> SignalUndoneRedone;

	virtual ~IHistory() = default;

	virtual void Do(ICommandPtr && command) = 0;

	virtual void Lock() = 0;

	virtual void Unlock() = 0;

	virtual SignalUndoneRedone UndoneRedoneSignal()const = 0;
};
