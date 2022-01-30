#pragma once
#include <cairomm/context.h>
#include "ICanvas.hpp"

class CairoCanvas: public ICanvas
{
public:
	explicit CairoCanvas(Cairo::RefPtr<Cairo::Context> const& cr)
		:m_cr(cr)
	{}

	void SetColor(RGBAColor const& color)override
	{
		m_cr->set_source_rgba(color.r, color.g, color.b, color.a);
	}

	void SetDash(double on, double off)override;

	void SetLineWidth(double width)override
	{
		m_cr->set_line_width(width);
	}

	void MoveTo(double x, double y)override
	{
		m_cr->move_to(x, y);
	}

	void LineTo(double x, double y)override
	{
		m_cr->line_to(x, y);
	}

	void ClosePath()override
	{
		m_cr->close_path();
	}

	void DrawRectangle(Rectangle const& rect)override
	{
		m_cr->rectangle(rect.x, rect.y, rect.width, rect.height);
	}

	void DrawEllipse(Ellipse const& ellipse)override;

	void Stroke()override
	{
		m_cr->stroke();
	}

	void Fill()override
	{
		m_cr->fill();
	}

	void FillPreserve()override
	{
		m_cr->fill_preserve();
	}

private:
	Cairo::RefPtr<Cairo::Context> const& m_cr;
};
