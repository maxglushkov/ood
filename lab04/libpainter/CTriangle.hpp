#pragma once
#include "CShape.hpp"

class CTriangle: public CShape
{
public:
	CTriangle(Color color, Point const& vertex1, Point const& vertex2, Point const& vertex3)
		:CShape(color)
		,m_vertices{vertex1, vertex2, vertex3}
	{}

	void Draw(ICanvas & canvas)const override;

	Point GetVertex1()const
	{
		return m_vertices[0];
	}

	Point GetVertex2()const
	{
		return m_vertices[1];
	}

	Point GetVertex3()const
	{
		return m_vertices[2];
	}

private:
	Point m_vertices[3];
};
