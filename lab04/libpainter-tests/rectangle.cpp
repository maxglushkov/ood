#include <CRectangle.hpp>
#include "logging-canvas.hpp"

constexpr Color COLOR = Color::Red;
constexpr Point VERTICES[] = {
	{0.9, -7},
	{19, -7},
	{19, 5.5},
	{0.9, 5.5}
};

TEST_CASE("Creating rectangle with x1 < x2 && y1 < y2")
{
	const CRectangle rectangle(COLOR, VERTICES[0].x, VERTICES[0].y, VERTICES[2].x, VERTICES[2].y);

	REQUIRE(rectangle.GetColor() == COLOR);
	TestPointsEquality(rectangle.GetLeftTop(), VERTICES[0]);
	TestPointsEquality(rectangle.GetRightBottom(), VERTICES[2]);
}

TEST_CASE("Creating rectangle with x1 > x2")
{
	const CRectangle rectangle(COLOR, VERTICES[2].x, VERTICES[0].y, VERTICES[0].x, VERTICES[2].y);

	TestPointsEquality(rectangle.GetLeftTop(), VERTICES[0]);
	TestPointsEquality(rectangle.GetRightBottom(), VERTICES[2]);
}

TEST_CASE("Creating rectangle with y1 > y2")
{
	const CRectangle rectangle(COLOR, VERTICES[0].x, VERTICES[2].y, VERTICES[2].x, VERTICES[0].y);

	TestPointsEquality(rectangle.GetLeftTop(), VERTICES[0]);
	TestPointsEquality(rectangle.GetRightBottom(), VERTICES[2]);
}

TEST_CASE("Drawing rectangle")
{
	CLoggingCanvas canvas;

	CRectangle(COLOR, VERTICES[0].x, VERTICES[0].y, VERTICES[2].x, VERTICES[2].y).Draw(canvas);

	canvas.Match({
		COLOR,
		Line{VERTICES[0], VERTICES[1]},
		Line{VERTICES[1], VERTICES[2]},
		Line{VERTICES[2], VERTICES[3]},
		Line{VERTICES[3], VERTICES[0]}
	});
}
