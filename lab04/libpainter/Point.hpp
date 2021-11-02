#pragma once
#include <istream>

struct Point
{
	double x, y;
};

inline std::istream & operator >>(std::istream & input, Point & point)
{
	return input >> point.x >> point.y;
}
