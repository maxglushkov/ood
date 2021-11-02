#pragma once
#include "CShape.hpp"

class CEllipse: public CShape
{
public:
	CEllipse(Color color, Point const& center, double xRadius, double yRadius)
		:CShape(color)
		,m_center(center)
		,m_horizontalRadius(xRadius)
		,m_verticalRadius(yRadius)
	{
		if (xRadius < 0 || yRadius < 0)
		{
			throw std::invalid_argument("ellipse radii should not be negative");
		}
	}

	void Draw(ICanvas & canvas)const override;

	Point GetCenter()const
	{
		return m_center;
	}

	double GetHorizontalRadius()const
	{
		return m_horizontalRadius;
	}

	double GetVerticalRadius()const
	{
		return m_verticalRadius;
	}

private:
	Point m_center;
	double m_horizontalRadius, m_verticalRadius;
};
