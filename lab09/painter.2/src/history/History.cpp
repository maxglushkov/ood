#include <stdexcept>
#include "History.hpp"

constexpr static char ERROR_LOCKED[] = "command history is locked";
constexpr static char ERROR_NOTHING_TO_COMMIT[] = "command history: nothing to commit";

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
	if (IsLocked())
	{
		throw std::logic_error(ERROR_LOCKED);
	}

	ICommand *const cmd = command.get();
	Push(std::move(command));
	cmd->Do();
}

void History::BeginOperation(ICommandPtr && doneCommand)
{
	if (IsLocked())
	{
		throw std::logic_error(ERROR_LOCKED);
	}

	m_operation = std::move(doneCommand);
}

void History::Commit()
{
	if (!m_operation)
	{
		throw std::logic_error(ERROR_NOTHING_TO_COMMIT);
	}

	Push(std::move(m_operation));
}

bool History::CanUndo()const
{
	return !IsLocked() && m_pos != m_history.cbegin();
}

bool History::CanRedo()const
{
	return !IsLocked() && m_pos != m_history.cend();
}

void History::Push(ICommandPtr && command)
{
	m_pos = m_history.erase(m_pos, m_history.cend());
	m_history.push_back(std::move(command));
	m_pos = m_history.cend();
}
