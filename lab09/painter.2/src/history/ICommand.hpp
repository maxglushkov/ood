#pragma once

struct ICommand
{
	ICommand() = default;

	ICommand(ICommand const&) = delete;
	ICommand(ICommand &&) = delete;
	ICommand & operator =(ICommand const&) = delete;
	ICommand & operator =(ICommand &&) = delete;

	virtual ~ICommand() = default;

	virtual void Do()noexcept = 0;

	virtual void Undo()noexcept = 0;
};
