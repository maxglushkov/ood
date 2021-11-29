#include <catch2/catch.hpp>
#include "../CDocumentItem.hpp"
#include "null-items.hpp"

TEST_CASE("CDocumentItem: getting image from image item")
{
	const auto image = std::make_shared<NullImage>();
	REQUIRE(CDocumentItem(image).GetImage() == image);
}

TEST_CASE("CDocumentItem: getting image from paragraph item")
{
	const auto paragraph = std::make_shared<NullParagraph>();
	REQUIRE_FALSE(CDocumentItem(paragraph).GetImage());
}

TEST_CASE("CDocumentItem: getting paragraph from image item")
{
	const auto image = std::make_shared<NullImage>();
	REQUIRE_FALSE(CDocumentItem(image).GetParagraph());
}

TEST_CASE("CDocumentItem: getting paragraph from paragraph item")
{
	const auto paragraph = std::make_shared<NullParagraph>();
	REQUIRE(CDocumentItem(paragraph).GetParagraph() == paragraph);
}

TEST_CASE("CDocumentItem: CConstDocumentItem functions")
{
	const auto paragraph = std::make_shared<NullParagraph>();
	const CDocumentItem paragraphItem(paragraph);
	REQUIRE_FALSE(paragraphItem.GetImage());
	REQUIRE(paragraphItem.GetParagraph() == paragraph);
}
