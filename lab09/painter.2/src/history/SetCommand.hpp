#pragma once
#include <utility>
#include "ICommand.hpp"

template<typename T>
class SetCommand: public ICommand
{
public:
	SetCommand(T & dest, T const& src)
		:m_dest(dest)
		,m_src(src)
	{}

	void Do()noexcept override
	{
		std::swap(m_dest, m_src);
	}

	void Undo()noexcept override
	{
		Do();
	}

private:
	T & m_dest, m_src;
};
