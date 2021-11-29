#include <catch2/catch.hpp>
#include "../CSetCommand.hpp"

constexpr static int OLD_VALUE = 0xbeef;
constexpr static int NEW_VALUE = 0xdead;

TEST_CASE("CSetCommand: constructing")
{
	int value = OLD_VALUE;
	CSetCommand command(value, NEW_VALUE);
	REQUIRE(value == OLD_VALUE);
}

TEST_CASE("CSetCommand: doing")
{
	int value = OLD_VALUE;
	CSetCommand command(value, NEW_VALUE);
	command.Do();
	REQUIRE(value == NEW_VALUE);
}

TEST_CASE("CSetCommand: undoing")
{
	int value = OLD_VALUE;
	CSetCommand command(value, NEW_VALUE);
	command.Do();
	command.Do();
	REQUIRE(value == OLD_VALUE);
}
