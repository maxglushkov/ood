#include <catch2/catch.hpp>
#include "../CDocumentItem.hpp"
#include "null-items.hpp"

TEST_CASE("CConstDocumentItem: getting image from image item")
{
	const auto image = std::make_shared<NullImage>();
	CConstDocumentItem const& imageItem = CDocumentItem(image);
	REQUIRE(imageItem.GetImage() == image);
}

TEST_CASE("CConstDocumentItem: getting image from paragraph item")
{
	const auto paragraph = std::make_shared<NullParagraph>();
	CConstDocumentItem const& paragraphItem = CDocumentItem(paragraph);
	REQUIRE_FALSE(paragraphItem.GetImage());
}

TEST_CASE("CConstDocumentItem: getting paragraph from image item")
{
	const auto image = std::make_shared<NullImage>();
	CConstDocumentItem const& imageItem = CDocumentItem(image);
	REQUIRE_FALSE(imageItem.GetParagraph());
}

TEST_CASE("CConstDocumentItem: getting paragraph from paragraph item")
{
	const auto paragraph = std::make_shared<NullParagraph>();
	CConstDocumentItem const& paragraphItem = CDocumentItem(paragraph);
	REQUIRE(paragraphItem.GetParagraph() == paragraph);
}
