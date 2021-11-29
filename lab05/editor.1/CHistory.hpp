#pragma once
#include <list>
#include "ICommand.hpp"

class CHistory
{
public:
	constexpr static size_t MAX_SIZE = 10;

	bool CanUndo()const
	{
		return m_pos != m_history.cbegin();
	}

	bool CanRedo()const
	{
		return m_pos != m_history.cend();
	}

	void Undo()
	{
		if (!CanUndo())
		{
			throw std::logic_error("nothing to undo");
		}
		--m_pos;
		(*m_pos)->Do();
	}

	void Redo()
	{
		if (!CanRedo())
		{
			throw std::logic_error("nothing to redo");
		}
		(*m_pos)->Do();
		++m_pos;
	}

	void Do(ICommandPtr && command)
	{
		(*m_history.insert(m_pos, std::move(command)))->Do();
		m_pos = m_history.erase(m_pos, m_history.cend());
		if (m_history.size() > MAX_SIZE)
		{
			m_history.erase(m_history.cbegin());
		}
	}

private:
	std::list<ICommandPtr> m_history;
	std::list<ICommandPtr>::iterator m_pos = m_history.end();
};
