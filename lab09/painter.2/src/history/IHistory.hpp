#pragma once
#include <memory>
#include <sigc++/signal.h>
#include "ICommand.hpp"

typedef std::unique_ptr<ICommand> ICommandPtr;

struct IHistory
{
	typedef sigc::signal<void()> SignalUndoneRedone;

	virtual ~IHistory() = default;

	virtual bool IsLocked()const = 0;

	virtual void Do(ICommandPtr && command) = 0;

	virtual void BeginOperation(ICommandPtr && doneCommand) = 0;

	virtual void Commit() = 0;

	virtual SignalUndoneRedone UndoneRedoneSignal()const = 0;
};
