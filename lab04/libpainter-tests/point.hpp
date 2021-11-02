#pragma once
#include <Point.hpp>
#include <catch2/catch.hpp>

inline void TestPointsEquality(Point const& l, Point const& r)
{
	REQUIRE(l.x == Approx(r.x));
	REQUIRE(l.y == Approx(r.y));
}
