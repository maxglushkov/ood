#pragma once
#include <ICanvas.hpp>
#include <variant>
#include "point.hpp"

struct Line
{
	const Point from, to;
};

struct Ellipse
{
	const Point center;
	const double xRadius, yRadius;
};

class CLoggingCanvas: public ICanvas
{
public:
	typedef std::variant<Color, Line, Ellipse> Command;

	void SetColor(Color color)override
	{
		m_log.push_back(color);
	}

	void DrawLine(Point const& from, Point const& to)override
	{
		m_log.push_back(Line{from, to});
	}

	void DrawEllipse(Point const& center, double xRadius, double yRadius)override
	{
		m_log.push_back(Ellipse{center, xRadius, yRadius});
	}

	void Match(std::initializer_list<Command> && commands)
	{
		REQUIRE(std::equal(m_log.begin(), m_log.end(), commands.begin(), commands.end()));
	}

private:
	std::vector<Command> m_log;
};

inline bool operator ==(Line const& l, Line const& r)
{
	TestPointsEquality(l.from, r.from);
	TestPointsEquality(l.to, r.to);
	return true;
}

inline bool operator ==(Ellipse const& l, Ellipse const& r)
{
	TestPointsEquality(l.center, r.center);
	REQUIRE(l.xRadius == Approx(r.xRadius));
	REQUIRE(l.yRadius == Approx(r.yRadius));
	return true;
}
