#pragma once
#include <CShape.hpp>

struct Shape: public CShape
{
	Shape(Color color):
		CShape(color)
	{}
};
