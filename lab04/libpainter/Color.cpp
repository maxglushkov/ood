#include <algorithm>
#include <istream>
#include "Color.hpp"

constexpr static std::pair<Color, char const*> COLOR_NAMES[] = {
	{Color::Green, "green"},
	{Color::Red, "red"},
	{Color::Blue, "blue"},
	{Color::Yellow, "yellow"},
	{Color::Pink, "pink"},
	{Color::Black, "black"}
};

std::istream & operator >>(std::istream & input, Color & color)
{
	std::string colorName;
	input >> colorName;
	if (auto iter = std::find_if(
		std::begin(COLOR_NAMES), std::end(COLOR_NAMES),
		[&](auto const& pair)
		{
			return pair.second == colorName;
		}
	); iter != std::end(COLOR_NAMES))
	{
		color = iter->first;
	}
	else
	{
		input.setstate(std::ios::failbit);
	}
	return input;
}

std::ostream & operator <<(std::ostream & output, Color color)
{
	return output << COLOR_NAMES[unsigned(color)].second;
}
