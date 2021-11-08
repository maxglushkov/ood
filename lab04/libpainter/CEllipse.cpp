#include "CEllipse.hpp"

void CEllipse::DrawOutline(ICanvas & canvas)const
{
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}
