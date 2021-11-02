#include <CRegularPolygon.hpp>
#include <cfloat>
#include "logging-canvas.hpp"

constexpr Color COLOR = Color::Yellow;
constexpr Point CENTER = {1, -1};
constexpr double OUTER_RADIUS = 9;

TEST_CASE("Creating regular polygon with 3 vertices")
{
	constexpr unsigned VERTEX_COUNT = 3;
	const CRegularPolygon polygon(COLOR, VERTEX_COUNT, CENTER, OUTER_RADIUS);

	REQUIRE(polygon.GetColor() == COLOR);
	REQUIRE(polygon.GetVertexCount() == VERTEX_COUNT);
	TestPointsEquality(polygon.GetCenter(), CENTER);
	REQUIRE(polygon.GetOuterRadius() == Approx(OUTER_RADIUS));
}

TEST_CASE("Creating regular polygon with no vertices")
{
	REQUIRE_THROWS(CRegularPolygon(COLOR, 0, CENTER, 0));
}

TEST_CASE("Creating regular polygon with single vertex and non-zero outer radius")
{
	REQUIRE_THROWS(CRegularPolygon(COLOR, 1, CENTER, DBL_MIN));
}

TEST_CASE("Creating regular polygon with single vertex and zero outer radius")
{
	constexpr unsigned VERTEX_COUNT = 1;
	const CRegularPolygon polygon(COLOR, VERTEX_COUNT, CENTER, 0);

	REQUIRE(polygon.GetVertexCount() == VERTEX_COUNT);
	TestPointsEquality(polygon.GetCenter(), CENTER);
	REQUIRE(polygon.GetOuterRadius() == Approx(0));
}

TEST_CASE("Drawing regular polygon with 3 vertices")
{
	constexpr unsigned VERTEX_COUNT = 3;
	constexpr Point VERTICES[] = {
		{10, -1},
		{-3.5, 6.794229},
		{-3.5, -8.794229}
	};
	CLoggingCanvas canvas;

	CRegularPolygon(COLOR, VERTEX_COUNT, CENTER, OUTER_RADIUS).Draw(canvas);

	canvas.Match({
		COLOR,
		Line{VERTICES[0], VERTICES[1]},
		Line{VERTICES[1], VERTICES[2]},
		Line{VERTICES[2], VERTICES[0]}
	});
}
