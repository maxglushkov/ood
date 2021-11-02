#include <sstream>
#include "CEllipse.hpp"
#include "CRectangle.hpp"
#include "CRegularPolygon.hpp"
#include "CShapeFactory.hpp"
#include "CTriangle.hpp"

static std::unique_ptr<CEllipse> CreateEllipse(std::istream & description)
{
	Point center;
	double xRadius, yRadius;
	Color color;
	if (description >> center >> xRadius >> yRadius >> color)
	{
		return std::make_unique<CEllipse>(color, center, xRadius, yRadius);
	}
	throw std::invalid_argument("ellipse format: <center x> <center y> <x radius> <y radius> <color>");
}

static std::unique_ptr<CRectangle> CreateRectangle(std::istream & description)
{
	Point v1, v2;
	Color color;
	if (description >> v1 >> v2 >> color)
	{
		return std::make_unique<CRectangle>(color, v1.x, v1.y, v2.x, v2.y);
	}
	throw std::invalid_argument("rectangle format: <x1> <y1> <x2> <y2> <color>");
}

static std::unique_ptr<CRegularPolygon> CreateRegularPolygon(std::istream & description)
{
	unsigned vertexCount;
	Point center;
	double outerRadius;
	Color color;
	if (description >> vertexCount >> center >> outerRadius >> color)
	{
		return std::make_unique<CRegularPolygon>(color, vertexCount, center, outerRadius);
	}
	throw std::invalid_argument("regular_polygon format: <vertex count> <center x> <center y> <outer radius> <color>");
}

static std::unique_ptr<CTriangle> CreateTriangle(std::istream & description)
{
	Point v1, v2, v3;
	Color color;
	if (description >> v1 >> v2 >> v3 >> color)
	{
		return std::make_unique<CTriangle>(color, v1, v2, v3);
	}
	throw std::invalid_argument("triangle format: <x1> <y1> <x2> <y2> <x3> <y3> <color>");
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream desc(description);
	std::string shapeName;
	desc >> shapeName;
	if (shapeName == "ellipse")
	{
		return CreateEllipse(desc);
	}
	if (shapeName == "rectangle")
	{
		return CreateRectangle(desc);
	}
	if (shapeName == "regular_polygon")
	{
		return CreateRegularPolygon(desc);
	}
	if (shapeName == "triangle")
	{
		return CreateTriangle(desc);
	}
	throw std::invalid_argument("unknown shape");
}
