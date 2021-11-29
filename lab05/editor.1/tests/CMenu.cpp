#include <catch2/catch.hpp>
#include "../CMenu.hpp"

static const CMenu MENU = {
	{
		"Echo",
		"prints specified string",
		[](CArguments & args, std::ostream & output)
		{
			output << args.PopLine();
		}
	}
};

TEST_CASE("CMenu: empty input")
{
	std::stringstream in, out, err;
	MENU.Run(in, out, err);

	REQUIRE(in.eof());
	REQUIRE(out.str() == "> ");
	REQUIRE(err.str().empty());
}

TEST_CASE("CMenu: unknown command")
{
	std::stringstream in("Quit"), out, err;
	MENU.Run(in, out, err);

	REQUIRE(in.eof());
	REQUIRE(out.str() == "> > ");
	REQUIRE(err.str() == "Error: unknown command\n");
}

TEST_CASE("CMenu: known command")
{
	std::stringstream in("Echo some str\t"), out, err;
	MENU.Run(in, out, err);

	REQUIRE(in.eof());
	REQUIRE(out.str() == "> some str\t> ");
	REQUIRE(err.str().empty());
}

TEST_CASE("CMenu: getting items")
{
	auto & items = MENU.GetItems();
	REQUIRE(items.size() == 1);
	REQUIRE(items[0].name == "Echo");
}
