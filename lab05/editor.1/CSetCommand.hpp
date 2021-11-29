#pragma once
#include "ICommand.hpp"

template<typename T>
class CSetCommand: public ICommand
{
public:
	CSetCommand(T & dest, T const& src)
		:m_dest(dest)
		,m_src(src)
	{}

	void Do()noexcept override
	{
		std::swap(m_dest, m_src);
	}

private:
	T & m_dest, m_src;
};
