#include "CSvgCanvas.hpp"

CSvgCanvas::CSvgCanvas(std::ostream & output)
	:m_output(output)
{
	m_output << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
	m_output << "<svg version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n";
}

CSvgCanvas::~CSvgCanvas()
{
	m_output << "</svg>";
}

void CSvgCanvas::SetColor(Color color)
{
	m_color = color;
}

void CSvgCanvas::DrawLine(Point const& from, Point const& to)
{
	m_output << "\t<line x1=\"" << from.x
	              << "\" y1=\"" << from.y
	              << "\" x2=\"" << to.x
	              << "\" y2=\"" << to.y
	              << "\" stroke=\"" << m_color
	              << "\" />\n";
}

void CSvgCanvas::DrawEllipse(Point const& center, double xRadius, double yRadius)
{
	m_output << "\t<ellipse cx=\"" << center.x
	                 << "\" cy=\"" << center.y
	                 << "\" rx=\"" << xRadius
	                 << "\" ry=\"" << yRadius
	                 << "\" stroke=\"" << m_color
	                 << "\" fill=\"transparent\" />\n";
}
