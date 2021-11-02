#pragma once
#include "Color.hpp"
#include "Point.hpp"

struct ICanvas
{
	virtual ~ICanvas() = default;

	virtual void SetColor(Color color) = 0;

	virtual void DrawLine(Point const& from, Point const& to) = 0;

	virtual void DrawEllipse(Point const& center, double xRadius, double yRadius) = 0;
};
