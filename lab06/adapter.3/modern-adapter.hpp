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

	void SetColor(uint32_t rgbColor)override
	{
		m_color.r = (rgbColor >> 16 & 0xff) / 255.0;
		m_color.g = (rgbColor >> 8 & 0xff) / 255.0;
		m_color.b = (rgbColor & 0xff) / 255.0;
	}

	void MoveTo(int x, int y)override
	{
		m_cursorPos = {x, y};
	}

	void LineTo(int x, int y)override
	{
		DrawLine(m_cursorPos, {x, y}, m_color);
		MoveTo(x, y);
	}

private:
	modern_graphics_lib::CPoint m_cursorPos{0, 0};
	modern_graphics_lib::CRGBAColor m_color{0, 0, 0, 1};
};
}
