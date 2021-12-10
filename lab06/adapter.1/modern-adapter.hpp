#pragma once
#include "graphics-lib.hpp"
#include "modern-graphics-lib.hpp"

namespace app
{
class CModernGraphicsCanvas: public graphics_lib::ICanvas
{
public:
	explicit CModernGraphicsCanvas(modern_graphics_lib::CModernGraphicsRenderer & renderer)
		:m_renderer(renderer)
	{}

	void MoveTo(int x, int y)override
	{
		m_cursorPos = {x, y};
	}

	void LineTo(int x, int y)override
	{
		m_renderer.DrawLine(m_cursorPos, {x, y});
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CModernGraphicsRenderer & m_renderer;
	modern_graphics_lib::CPoint m_cursorPos{0, 0};
};
}
