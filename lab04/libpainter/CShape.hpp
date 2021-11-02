#pragma once
#include "ICanvas.hpp"

class CShape
{
public:
	virtual ~CShape() = default;

	virtual void Draw(ICanvas & canvas)const
	{
		canvas.SetColor(m_color);
	}

	Color GetColor()const
	{
		return m_color;
	}

protected:
	CShape(Color color)
		:m_color(color)
	{}

private:
	Color m_color;
};
