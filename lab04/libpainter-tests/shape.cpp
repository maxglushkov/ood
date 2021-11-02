#include "logging-canvas.hpp"
#include "shape.hpp"

TEST_CASE("Shapes with different colors")
{
	REQUIRE(Shape(Color::Green).GetColor() == Color::Green);
	REQUIRE(Shape(Color::Red).GetColor() == Color::Red);
}

TEST_CASE("Drawing green shape on canvas")
{
	constexpr Color COLOR = Color::Green;
	CLoggingCanvas canvas;

	Shape(COLOR).Draw(canvas);

	canvas.Match({COLOR});
}

TEST_CASE("Drawing red shape on canvas")
{
	constexpr Color COLOR = Color::Red;
	CLoggingCanvas canvas;

	Shape(COLOR).Draw(canvas);

	canvas.Match({COLOR});
}
