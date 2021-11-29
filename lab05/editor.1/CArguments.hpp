#pragma once
#include <optional>
#include <sstream>

class CArguments
{
public:
	CArguments(std::string const& args)
		:m_args(args)
	{}

	std::string PopLine()
	{
		std::string line;
		std::getline(m_args >> std::ws, line);
		return line;
	}

	template<typename T>
	T Pop()
	{
		if (T value; m_args >> value)
		{
			return value;
		}
		throw std::invalid_argument("unable to parse command line argument");
	}

	std::optional<size_t> PopPosition()
	{
		constexpr static char POSITION_END[] = "end";
		const auto streamPos = m_args.tellg();
		if (Pop<std::string>() == POSITION_END)
		{
			return std::nullopt;
		}
		m_args.seekg(streamPos);
		return Pop<size_t>();
	}

private:
	std::istringstream m_args;
};
