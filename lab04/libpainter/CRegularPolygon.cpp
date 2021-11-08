#include "CRegularPolygon.hpp"

void CRegularPolygon::DrawOutline(ICanvas & canvas)const
{
	const double sideLengthInRadians = 2 * M_PI / m_vertexCount;
	Point first = {m_center.x + m_outerRadius, m_center.y};
	for (unsigned vertex = 1; vertex < m_vertexCount; ++vertex)
	{
		const double angle = vertex * sideLengthInRadians;
		const Point second = {
			m_center.x + m_outerRadius * cos(angle),
			m_center.y + m_outerRadius * sin(angle)
		};
		canvas.DrawLine(first, second);
		first = second;
	}
	canvas.DrawLine(first, {m_center.x + m_outerRadius, m_center.y});
}
