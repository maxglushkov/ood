#include "CRectangle.hpp"

void CRectangle::Draw(ICanvas & canvas)const
{
	CShape::Draw(canvas);
	const Point rightTop = {m_rightBottom.x, m_leftTop.y};
	const Point leftBottom = {m_leftTop.x, m_rightBottom.y};
	canvas.DrawLine(m_leftTop, rightTop);
	canvas.DrawLine(rightTop, m_rightBottom);
	canvas.DrawLine(m_rightBottom, leftBottom);
	canvas.DrawLine(leftBottom, m_leftTop);
}
