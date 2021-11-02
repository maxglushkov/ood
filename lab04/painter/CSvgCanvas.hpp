#pragma once
#include <ICanvas.hpp>

class CSvgCanvas: public ICanvas
{
public:
	CSvgCanvas(std::ostream & output);

	~CSvgCanvas()override;

	void SetColor(Color color)override;

	void DrawLine(Point const& from, Point const& to)override;

	void DrawEllipse(Point const& center, double xRadius, double yRadius)override;

private:
	std::ostream & m_output;
	Color m_color = Color::Black;
};
