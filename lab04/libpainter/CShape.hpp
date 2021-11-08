#pragma once
#include "ICanvas.hpp"

class CShape
{
public:
	virtual ~CShape() = default;

	void Draw(ICanvas & canvas)const
	{
		canvas.SetColor(m_color);
		DrawOutline(canvas);
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

	virtual void DrawOutline(ICanvas & canvas)const = 0;
};
