#pragma once
#include <deque>
#include "IHistory.hpp"

class History: public IHistory, virtual public sigc::trackable
{
public:
	void Undo()noexcept;

	void Redo()noexcept;

	bool IsLocked()const override
	{
		return bool(m_operation);
	}

	void Do(ICommandPtr && command)override;

	void BeginOperation(ICommandPtr && doneCommand)override;

	void Commit()override;

	SignalUndoneRedone UndoneRedoneSignal()const override
	{
		return m_sigUndoneRedone;
	}

private:
	typedef std::deque<ICommandPtr>::const_iterator Iterator;

	std::deque<ICommandPtr> m_history;
	Iterator m_pos = m_history.cend();
	ICommandPtr m_operation;

	SignalUndoneRedone m_sigUndoneRedone;

	bool CanUndo()const;

	bool CanRedo()const;

	void Push(ICommandPtr && command);
};
