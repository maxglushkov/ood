#pragma once
#include <list>
#include "ICommand.hpp"

template<typename T>
class ListCommand: public ICommand
{
public:
	typedef typename std::list<T>::const_iterator Iterator;

	ListCommand(std::list<T> & list, Iterator insertBefore, T && item)
		:m_inserted(list)
		,m_insertedIt(insertBefore)
		,m_erasedIt(m_erased.insert(m_erased.cend(), std::move(item)))
	{}

	ListCommand(std::list<T> & list, Iterator eraseAt)
		:m_inserted(list)
		,m_insertedIt(eraseAt)
		,m_erasedIt(m_erased.cend())
	{}

	void Do()noexcept override
	{
		if (m_erasedIt == m_erased.cend())
		{
			m_erased.splice(m_erasedIt, m_inserted, m_insertedIt++);
			--m_erasedIt;
		}
		else
		{
			m_inserted.splice(m_insertedIt, m_erased, m_erasedIt);
			--m_insertedIt;
			m_erasedIt = m_erased.cend();
		}
	}

	void Undo()noexcept override
	{
		Do();
	}

private:
	static std::list<T> m_erased;

	std::list<T> & m_inserted;
	Iterator m_insertedIt, m_erasedIt;
};

template<typename T>
std::list<T> ListCommand<T>::m_erased;
