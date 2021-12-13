#pragma once
#include <sstream>

class CArguments
{
public:
	CArguments(std::string const& args)
		:m_args(args)
	{}

	template<typename T>
	T Pop()
	{
		if (T value; m_args >> value)
		{
			return value;
		}
		throw std::invalid_argument("unable to parse command line argument");
	}

private:
	std::istringstream m_args;
};
