#include <catch2/catch.hpp>
#include "../CArguments.hpp"

constexpr static char TEXT_ARGS[] = " C0mm&nd	 Line ";
constexpr static char NUMERIC_ARGS[] = "	2 -1	end End";

TEST_CASE("CArguments: taking line")
{
	REQUIRE(CArguments(TEXT_ARGS).PopLine() == "C0mm&nd	 Line ");
}

TEST_CASE("CArguments: taking words")
{
	CArguments args(TEXT_ARGS);
	REQUIRE(args.Pop<std::string>() == "C0mm&nd");
	REQUIRE(args.Pop<std::string>() == "Line");
}

TEST_CASE("CArguments: taking word and line")
{
	CArguments args(TEXT_ARGS);
	REQUIRE(args.Pop<std::string>() == "C0mm&nd");
	REQUIRE(args.PopLine() == "Line ");
}

TEST_CASE("CArguments: taking integers")
{
	CArguments args(NUMERIC_ARGS);
	REQUIRE(args.Pop<int>() == 2);
	REQUIRE(args.Pop<int>() == -1);
	REQUIRE_THROWS(args.Pop<int>());
}

TEST_CASE("CArguments: taking positions")
{
	CArguments args(NUMERIC_ARGS);
	REQUIRE(*args.PopPosition() == 2);
	REQUIRE(*args.PopPosition() == -1);
	REQUIRE_FALSE(args.PopPosition().has_value());
	REQUIRE_THROWS(args.PopPosition());
}
