#include "History.hpp"

void History::Undo()noexcept
{
	if (CanUndo())
	{
		--m_pos;
		(*m_pos)->Undo();
		m_sigUndoneRedone();
	}
}

void History::Redo()noexcept
{
	if (CanRedo())
	{
		(*m_pos)->Do();
		++m_pos;
		m_sigUndoneRedone();
	}
}

void History::Do(ICommandPtr && command)
{
	m_pos = m_history.erase(m_pos, m_history.cend());
	m_history.emplace_back(std::move(command))->Do();
	m_pos = m_history.cend();
}

bool History::CanUndo()const
{
	return !m_lock && m_pos != m_history.cbegin();
}

bool History::CanRedo()const
{
	return !m_lock && m_pos != m_history.cend();
}
