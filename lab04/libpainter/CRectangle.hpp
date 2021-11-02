#pragma once
#include "CShape.hpp"

class CRectangle: public CShape
{
public:
	CRectangle(Color color, double x1, double y1, double x2, double y2)
		:CShape(color)
		,m_leftTop{std::min(x1, x2), std::min(y1, y2)}
		,m_rightBottom{std::max(x1, x2), std::max(y1, y2)}
	{}

	void Draw(ICanvas & canvas)const override;

	Point GetLeftTop()const
	{
		return m_leftTop;
	}

	Point GetRightBottom()const
	{
		return m_rightBottom;
	}

private:
	Point m_leftTop, m_rightBottom;
};
