#include "CairoCanvas.hpp"

void CairoCanvas::SetDash(double on, double off)
{
	m_cr->set_dash(std::vector{on, off}, 0);
}

void CairoCanvas::DrawEllipse(Ellipse const& ellipse)
{
	m_cr->save();
	m_cr->translate(ellipse.cx, ellipse.cy);
	m_cr->scale(ellipse.rx, ellipse.ry);
	m_cr->arc(0.0, 0.0, 1.0, 0.0, 2.0 * M_PI);
	m_cr->restore();
}
