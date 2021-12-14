#pragma once
#include "graphics-lib.hpp"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point & p1, const Point & p2, const Point & p3, uint32_t color = 0)
		:m_vertices{p1, p2, p3}
		,m_color(color)
	{}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_vertices[0].x, m_vertices[0].y);
		canvas.LineTo(m_vertices[1].x, m_vertices[1].y);
		canvas.LineTo(m_vertices[2].x, m_vertices[2].y);
		canvas.LineTo(m_vertices[0].x, m_vertices[0].y);
	}
private:
	Point m_vertices[3];
	uint32_t m_color;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point & leftTop, int width, int height, uint32_t color = 0)
		:m_leftTop(leftTop)
		,m_width(width)
		,m_height(height)
		,m_color(color)
	{}

	void Draw(graphics_lib::ICanvas & canvas)const override
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}
private:
	Point m_leftTop;
	int m_width, m_height;
	uint32_t m_color;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib::ICanvas & canvas)
		:m_canvas(canvas)
	{}
	void Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(m_canvas);
	}
private:
	graphics_lib::ICanvas & m_canvas;
};
}
