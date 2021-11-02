#include <CEllipse.hpp>
#include <CRectangle.hpp>
#include <CRegularPolygon.hpp>
#include <CShapeFactory.hpp>
#include <CTriangle.hpp>
#include "point.hpp"

TEST_CASE("Fabricating ellipse")
{
	const auto shape = CShapeFactory().CreateShape("ellipse 10.1 -1.01 4 3 green");

	auto & ellipse = dynamic_cast<CEllipse const&>(*shape);
	TestPointsEquality(ellipse.GetCenter(), {10.1, -1.01});
	REQUIRE(ellipse.GetHorizontalRadius() == Approx(4));
	REQUIRE(ellipse.GetVerticalRadius() == Approx(3));
	REQUIRE(ellipse.GetColor() == Color::Green);
}

TEST_CASE("Fabricating ellipse with invalid double argument")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("ellipse 10.1 -1.01 0x4 3 green"));
}

TEST_CASE("Fabricating ellipse with invalid color")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("ellipse 10.1 -1.01 4 3 white"));
}

TEST_CASE("Fabricating rectangle")
{
	const auto shape = CShapeFactory().CreateShape("rectangle 0.9 -7 19 5.5 red");

	auto & rectangle = dynamic_cast<CRectangle const&>(*shape);
	TestPointsEquality(rectangle.GetLeftTop(), {0.9, -7});
	TestPointsEquality(rectangle.GetRightBottom(), {19, 5.5});
	REQUIRE(rectangle.GetColor() == Color::Red);
}

TEST_CASE("Fabricating rectangle with invalid argument")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("rectangle 0.9 - 19 5.5 red"));
}

TEST_CASE("Fabricating regular polygon")
{
	const auto shape = CShapeFactory().CreateShape("regular_polygon 3 1 -1 9 yellow");

	auto & polygon = dynamic_cast<CRegularPolygon const&>(*shape);
	REQUIRE(polygon.GetVertexCount() == 3);
	TestPointsEquality(polygon.GetCenter(), {1, -1});
	REQUIRE(polygon.GetOuterRadius() == Approx(9));
	REQUIRE(polygon.GetColor() == Color::Yellow);
}

TEST_CASE("Fabricating regular polygon with invalid argument")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("regular_polygon 3.0 1 -1 9 yellow"));
}

TEST_CASE("Fabricating triangle")
{
	const auto shape = CShapeFactory().CreateShape("triangle 1.5 2 2 0 3 -0.01 black");

	auto & triangle = dynamic_cast<CTriangle const&>(*shape);
	TestPointsEquality(triangle.GetVertex1(), {1.5, 2});
	TestPointsEquality(triangle.GetVertex2(), {2, 0});
	TestPointsEquality(triangle.GetVertex3(), {3, -0.01});
	REQUIRE(triangle.GetColor() == Color::Black);
}

TEST_CASE("Fabricating triangle with invalid argument")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("triangle 1.5 2 2 0 nan -0.01 black"));
}

TEST_CASE("Fabricating empty shape")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape(""));
}

TEST_CASE("Fabricating unexistant shape")
{
	REQUIRE_THROWS(CShapeFactory().CreateShape("noshape"));
}
