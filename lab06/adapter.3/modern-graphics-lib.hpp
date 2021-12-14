#pragma once
#include <boost/format.hpp>

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
class CPoint
{
public:
	CPoint(int x, int y)
		:x(x)
		,y(y)
	{}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		:r(r)
		,g(g)
		,b(b)
		,a(a)
	{}

	float r, g, b, a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(std::ostream & strm)
		:m_out(strm)
	{}

	~CModernGraphicsRenderer()
	{
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		if (m_drawing)
		{
			throw std::logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << std::endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor & color)
	{
		if (!m_drawing)
		{
			throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(
			R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">)""\n"
			R"(    <color r="%5%" g="%6%" b="%7%" a="%8%" />)""\n"
			R"(  </line>)"
		) % start.x % start.y % end.x % end.y % color.r % color.g % color.b % color.a << std::endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		if (!m_drawing)
		{
			throw std::logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << std::endl;
		m_drawing = false;
	}
private:
	std::ostream & m_out;
	bool m_drawing = false;
};
}
