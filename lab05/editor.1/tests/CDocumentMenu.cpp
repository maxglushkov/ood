#include "../CDocumentMenu.hpp"
#include "logging-document.hpp"

TEST_CASE("CDocumentMenu: inserting paragraph")
{
	std::stringstream in("InsertParagraph 0 &amp;"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		InsertParagraph{"&amp;", 0}
	});
}

TEST_CASE("CDocumentMenu: inserting image")
{
	std::stringstream in("InsertImage end 400 300 /"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		InsertImage{"/", 400, 300, std::nullopt}
	});
}

TEST_CASE("CDocumentMenu: setting title")
{
	std::stringstream in("SetTitle \t/end 400 300 "), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		SetTitle{"/end 400 300 "}
	});
}

TEST_CASE("CDocumentMenu: replacing text in paragraph item")
{
	std::stringstream in("ReplaceText 0 <b>text</b>"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	REQUIRE(err.str().empty());
	document.Match({
		GetItem{0}
	});
}

TEST_CASE("CDocumentMenu: replacing text in image item")
{
	std::stringstream in("ReplaceText 0 <b>text</b>"), out, err;
	CLoggingDocument document({std::make_shared<NullImage>()});
	CDocumentMenu(document).Run(in, out, err);

	REQUIRE(err.str() == "Error: requested item is not a paragraph\n");
	document.Match({
		GetItem{0}
	});
}

TEST_CASE("CDocumentMenu: resizing image in paragraph item")
{
	std::stringstream in("ResizeImage 0 300 400"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	REQUIRE(err.str() == "Error: requested item is not an image\n");
	document.Match({
		GetItem{0}
	});
}

TEST_CASE("CDocumentMenu: resizing image in image item")
{
	std::stringstream in("ResizeImage 0 300 400"), out, err;
	CLoggingDocument document({std::make_shared<NullImage>()});
	CDocumentMenu(document).Run(in, out, err);

	REQUIRE(err.str().empty());
	document.Match({
		GetItem{0}
	});
}

TEST_CASE("CDocumentMenu: deleting item")
{
	std::stringstream in("DeleteItem 0"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		DeleteItem{0}
	});
}

TEST_CASE("CDocumentMenu: undoing")
{
	std::stringstream in("Undo"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		Undo{}
	});
}

TEST_CASE("CDocumentMenu: redoing")
{
	std::stringstream in("Redo"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	document.Match({
		Redo{}
	});
}

TEST_CASE("CDocumentMenu: saving")
{
	std::stringstream in("Save /some/location"), out, err;
	CLoggingDocument document;
	CDocumentMenu(document).Run(in, out, err);

	REQUIRE(document.GetPath() == "/some/location");
}
