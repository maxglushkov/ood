#pragma once
#include <CShape.hpp>

struct Shape: public CShape
{
	Shape(Color color):
		CShape(color)
	{}

private:
	void DrawOutline([[maybe_unused]] ICanvas & canvas)const override
	{}
};
