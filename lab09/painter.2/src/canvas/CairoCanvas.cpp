#include "CairoCanvas.hpp"

void CairoCanvas::SetDash(double on, double off)
{
	m_cr->set_dash(std::vector{on, off}, 0);
}

void CairoCanvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	m_cr->save();
	m_cr->translate(cx, cy);
	m_cr->scale(rx, ry);
	m_cr->arc(0.0, 0.0, 1.0, 0.0, 2.0 * M_PI);
	m_cr->restore();
}
