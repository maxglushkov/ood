#include <CTriangle.hpp>
#include "logging-canvas.hpp"

constexpr Color COLOR = Color::Black;
constexpr Point VERTICES[] = {
	{1.5, 2},
	{2, 0},
	{3, -0.01}
};

TEST_CASE("Creating triangle")
{
	const CTriangle triangle(COLOR, VERTICES[0], VERTICES[1], VERTICES[2]);

	REQUIRE(triangle.GetColor() == COLOR);
	TestPointsEquality(triangle.GetVertex1(), VERTICES[0]);
	TestPointsEquality(triangle.GetVertex2(), VERTICES[1]);
	TestPointsEquality(triangle.GetVertex3(), VERTICES[2]);
}

TEST_CASE("Drawing triangle")
{
	CLoggingCanvas canvas;

	CTriangle(COLOR, VERTICES[0], VERTICES[1], VERTICES[2]).Draw(canvas);

	canvas.Match({
		COLOR,
		Line{VERTICES[0], VERTICES[1]},
		Line{VERTICES[1], VERTICES[2]},
		Line{VERTICES[2], VERTICES[0]}
	});
}
