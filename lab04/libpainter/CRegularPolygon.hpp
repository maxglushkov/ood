#pragma once
#include <cmath>
#include "CShape.hpp"

class CRegularPolygon: public CShape
{
public:
	CRegularPolygon(Color color, unsigned vertexCount, Point const& center, double outerRadius)
		:CShape(color)
		,m_vertexCount(vertexCount)
		,m_center(center)
		,m_outerRadius(outerRadius)
	{
		switch (vertexCount)
		{
			case 0:
				throw std::invalid_argument("polygon should have at least 1 vertex");
			case 1:
				if (std::fpclassify(outerRadius) != FP_ZERO)
				{
					throw std::invalid_argument("polygon with single vertex should have zero radius");
				}
		}
	}

	unsigned GetVertexCount()const
	{
		return m_vertexCount;
	}

	Point GetCenter()const
	{
		return m_center;
	}

	double GetOuterRadius()const
	{
		return m_outerRadius;
	}

private:
	unsigned m_vertexCount;
	Point m_center;
	double m_outerRadius;

	void DrawOutline(ICanvas & canvas)const override;
};
