#include "CTriangle.hpp"

void CTriangle::DrawOutline(ICanvas & canvas)const
{
	canvas.DrawLine(m_vertices[0], m_vertices[1]);
	canvas.DrawLine(m_vertices[1], m_vertices[2]);
	canvas.DrawLine(m_vertices[2], m_vertices[0]);
}
