#pragma once
#include "../drawing/shapes.hpp"

struct ICanvas
{
	virtual ~ICanvas() = default;

	virtual void SetColor(RGBAColor const& color) = 0;

	virtual void SetDash(double on, double off) = 0;

	virtual void SetLineWidth(double width) = 0;

	virtual void MoveTo(double x, double y) = 0;

	virtual void LineTo(double x, double y) = 0;

	virtual void ClosePath() = 0;

	virtual void DrawRectangle(Rectangle const& rect) = 0;

	virtual void DrawEllipse(Ellipse const& ellipse) = 0;

	virtual void Stroke() = 0;

	virtual void Fill() = 0;

	virtual void FillPreserve() = 0;
};
