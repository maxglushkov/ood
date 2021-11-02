#pragma once
#include <iosfwd>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

std::istream & operator >>(std::istream & input, Color & color);

std::ostream & operator <<(std::ostream & output, Color color);
