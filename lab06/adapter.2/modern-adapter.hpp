#pragma once
#include "graphics-lib.hpp"
#include "modern-graphics-lib.hpp"

namespace app
{
class CModernGraphicsCanvas: public graphics_lib::ICanvas, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsCanvas(std::ostream & surface)
		:modern_graphics_lib::CModernGraphicsRenderer(surface)
	{
		BeginDraw();
	}

	void MoveTo(int x, int y)override
	{
		m_cursorPos = {x, y};
	}

	void LineTo(int x, int y)override
	{
		DrawLine(m_cursorPos, {x, y});
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CPoint m_cursorPos{0, 0};
};
}
