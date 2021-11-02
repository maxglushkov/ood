#include "CEllipse.hpp"

void CEllipse::Draw(ICanvas & canvas)const
{
	CShape::Draw(canvas);
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}
