#include <catch2/catch.hpp>
#include "../CParagraph.hpp"

constexpr static char INITIAL_TEXT[] = "Initial text";
constexpr static char UPDATED_TEXT[] = "Updated text";

TEST_CASE("CParagraph: getting text")
{
	CHistory history;
	REQUIRE(CParagraph(history, INITIAL_TEXT).GetText() == INITIAL_TEXT);
}

TEST_CASE("CParagraph: setting text")
{
	CHistory history;
	CParagraph paragraph(history, INITIAL_TEXT);
	paragraph.SetText(UPDATED_TEXT);
	REQUIRE(paragraph.GetText() == UPDATED_TEXT);
}
