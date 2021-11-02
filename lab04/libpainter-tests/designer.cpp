#include <CDesigner.hpp>
#include <catch2/catch.hpp>
#include <sstream>
#include "text-shape-factory.hpp"

TEST_CASE("Designing draft from empty input")
{
	std::istringstream input;
	TextShapeFactory factory;
	CDesigner designer(factory);

	const auto draft = designer.CreateDraft(input);

	REQUIRE(input.eof());
	REQUIRE(draft.begin() == draft.end());
}

TEST_CASE("Designing draft with shapes")
{
	std::istringstream input(" 1\n 2 \n  3 \n");
	TextShapeFactory factory;
	CDesigner designer(factory);

	const auto draft = designer.CreateDraft(input);

	REQUIRE(input.eof());
	auto it = draft.begin();
	REQUIRE(GetShapeText(*it++) == " 1");
	REQUIRE(GetShapeText(*it++) == " 2 ");
	REQUIRE(GetShapeText(*it++) == "  3 ");
	REQUIRE(it == draft.end());
}
