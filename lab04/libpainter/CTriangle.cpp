#include "CTriangle.hpp"

void CTriangle::Draw(ICanvas & canvas)const
{
	CShape::Draw(canvas);
	canvas.DrawLine(m_vertices[0], m_vertices[1]);
	canvas.DrawLine(m_vertices[1], m_vertices[2]);
	canvas.DrawLine(m_vertices[2], m_vertices[0]);
}
