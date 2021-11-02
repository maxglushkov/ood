#include <CEllipse.hpp>
#include "logging-canvas.hpp"

constexpr Color COLOR = Color::Green;
constexpr Point CENTER = {10.1, -1.01};
constexpr double X_RADIUS = 4;
constexpr double Y_RADIUS = 3;

TEST_CASE("Creating ellipse with positive radii")
{
	const CEllipse ellipse(COLOR, CENTER, X_RADIUS, Y_RADIUS);

	REQUIRE(ellipse.GetColor() == COLOR);
	TestPointsEquality(ellipse.GetCenter(), CENTER);
	REQUIRE(ellipse.GetHorizontalRadius() == Approx(X_RADIUS));
	REQUIRE(ellipse.GetVerticalRadius() == Approx(Y_RADIUS));
}

TEST_CASE("Creating ellipse with negative horizontal radius")
{
	REQUIRE_THROWS(CEllipse(COLOR, CENTER, -4, 3));
}

TEST_CASE("Creating ellipse with negative vertical radius")
{
	REQUIRE_THROWS(CEllipse(COLOR, CENTER, 4, -3));
}

TEST_CASE("Drawing ellipse")
{
	CLoggingCanvas canvas;

	CEllipse(COLOR, CENTER, X_RADIUS, Y_RADIUS).Draw(canvas);

	canvas.Match({
		COLOR,
		Ellipse{CENTER, X_RADIUS, Y_RADIUS}
	});
}
