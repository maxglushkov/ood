#pragma once
#include <memory>

class ICommand
{
public:
	ICommand() = default;

	ICommand(ICommand const&) = delete;
	ICommand(ICommand &&) = delete;
	ICommand & operator =(ICommand const&) = delete;
	ICommand & operator =(ICommand &&) = delete;

	virtual ~ICommand() = default;

	virtual void Do()noexcept = 0;
};

typedef std::unique_ptr<ICommand> ICommandPtr;
