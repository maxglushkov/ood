#pragma once
#include <deque>
#include "IHistory.hpp"

class History: public IHistory, virtual public sigc::trackable
{
public:
	void Undo()noexcept;

	void Redo()noexcept;

	void Do(ICommandPtr && command)override;

	void Lock()override
	{
		++m_lock;
	}

	void Unlock()override
	{
		--m_lock;
	}

	SignalUndoneRedone UndoneRedoneSignal()const override
	{
		return m_sigUndoneRedone;
	}

private:
	typedef std::deque<ICommandPtr>::const_iterator Iterator;

	std::deque<ICommandPtr> m_history;
	Iterator m_pos = m_history.cend();
	unsigned m_lock = 0;

	SignalUndoneRedone m_sigUndoneRedone;

	bool CanUndo()const;

	bool CanRedo()const;
};
