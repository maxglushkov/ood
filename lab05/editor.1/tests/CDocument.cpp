#include <catch2/catch.hpp>
#include <fstream>
#include "../CDocument.hpp"

TEST_CASE("CDocument: empty")
{
	const CDocument document;
	REQUIRE(document.GetItemsCount() == 0);
	REQUIRE(document.GetTitle().empty());
}

TEST_CASE("CDocument: inserting items at unexistant positions")
{
	CDocument document;
	REQUIRE_THROWS(document.InsertParagraph({}, 1));
	REQUIRE_THROWS(document.InsertImage({}, {}, {}, 1));
	REQUIRE(document.GetItemsCount() == 0);
}

TEST_CASE("CDocument: inserting paragraphs")
{
	constexpr static size_t ITEMS_COUNT = 3;
	std::shared_ptr<IParagraph> paragraphs[ITEMS_COUNT];
	CDocument document;

	paragraphs[0] = document.InsertParagraph({}, 0);
	paragraphs[2] = document.InsertParagraph({});
	paragraphs[1] = document.InsertParagraph({}, 1);

	REQUIRE(document.GetItemsCount() == ITEMS_COUNT);
	for (size_t index = 0; index < ITEMS_COUNT; ++index)
	{
		REQUIRE(document.GetItem(index).GetParagraph() == paragraphs[index]);
	}
}

TEST_CASE("CDocument: getting unexistant item")
{
	const CDocument constDoc;
	REQUIRE_THROWS(constDoc.GetItem(0));
	REQUIRE_THROWS(CDocument().GetItem(0));
}

TEST_CASE("CDocument: getting item")
{
	constexpr static char PARAGRAPH_TEXT[] = "Paragraph text";
	CDocument mutDoc;
	CDocument const& constDoc = mutDoc;

	const auto paragraph = mutDoc.InsertParagraph({});
	const auto mutParagraph = mutDoc.GetItem(0).GetParagraph();
	const auto constParagraph = constDoc.GetItem(0).GetParagraph();

	REQUIRE(mutParagraph == paragraph);
	REQUIRE(constParagraph == paragraph);
	mutParagraph->SetText(PARAGRAPH_TEXT);
	REQUIRE(constParagraph->GetText() == PARAGRAPH_TEXT);
}

TEST_CASE("CDocument: deleting unexistant item")
{
	REQUIRE_THROWS(CDocument().DeleteItem(0));
}

TEST_CASE("CDocument: deleting item")
{
	CDocument document;
	document.InsertParagraph({});
	document.DeleteItem(0);
	REQUIRE(document.GetItemsCount() == 0);
}

TEST_CASE("CDocument: setting title")
{
	constexpr static char TITLE[] = "Document title";
	CDocument document;
	document.SetTitle(TITLE);
	REQUIRE(document.GetTitle() == TITLE);
}

constexpr static std::string_view HTML = R"(<!DOCTYPE html>
<html>
	<head>
		<title></title>
	</head>
	<body>
		<p>&lt;script&gt;alert(1);&lt;/script&gt;</p>
	</body>
</html>)";

TEST_CASE("CDocument: saving")
{
	CDocument document;
	document.InsertParagraph("<script>alert(1);</script>");

	namespace fs = std::filesystem;
	const auto dirPath = fs::temp_directory_path() / "CDocumentTest";
	REQUIRE(fs::create_directory(dirPath));
	const auto filePath = dirPath / "saved.htm";
	document.Save(filePath);

	char data[4096];
	std::ifstream file(filePath);
	file.read(data, sizeof data);
	REQUIRE(data == HTML);
	file.close();

	fs::remove_all(dirPath);
}
