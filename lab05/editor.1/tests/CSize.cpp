#include <catch2/catch.hpp>
#include "../CSize.hpp"

constexpr int WIDTH = 400;
constexpr int HEIGHT = 300;

TEST_CASE("CSize: width range")
{
	REQUIRE_THROWS(CSize(CSize::MIN_SIZE - 1, HEIGHT));
	REQUIRE_NOTHROW(CSize(CSize::MIN_SIZE, HEIGHT));
	REQUIRE_NOTHROW(CSize(CSize::MAX_SIZE, HEIGHT));
	REQUIRE_THROWS(CSize(CSize::MAX_SIZE + 1, HEIGHT));
}

TEST_CASE("CSize: height range")
{
	REQUIRE_THROWS(CSize(WIDTH, CSize::MIN_SIZE - 1));
	REQUIRE_NOTHROW(CSize(WIDTH, CSize::MIN_SIZE));
	REQUIRE_NOTHROW(CSize(WIDTH, CSize::MAX_SIZE));
	REQUIRE_THROWS(CSize(WIDTH, CSize::MAX_SIZE + 1));
}

TEST_CASE("CSize: getting width and height")
{
	const CSize size(WIDTH, HEIGHT);
	REQUIRE(size.GetWidth() == WIDTH);
	REQUIRE(size.GetHeight() == HEIGHT);
}
