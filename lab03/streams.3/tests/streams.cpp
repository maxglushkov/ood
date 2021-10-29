#include <catch2/catch.hpp>
#include <filesystem>
#include "stream-tester.hpp"
#include "../file-stream.hpp"
#include "../memory-stream.hpp"

TEST_CASE("Testing file streams")
{
	const auto filename = std::filesystem::temp_directory_path() / "FileStreamsTest";
	{
		CFileOutputStream output(filename);
		CStreamTester::TestWrite(output);
	}
	{
		std::ifstream stdInput(filename);
		std::vector<uint8_t> data(CStreamTester::GetTestDataSize());
		stdInput.read(reinterpret_cast<char *>(data.data()), data.size());
		REQUIRE(data == CStreamTester::GetTestData());
	}
	{
		CFileInputStream input(filename);
		CStreamTester::TestRead(input);
	}
	std::filesystem::remove(filename);
}

TEST_CASE("Testing memory streams")
{
	std::vector<uint8_t> data;

	CMemoryOutputStream output(data);
	CStreamTester::TestWrite(output);

	REQUIRE(data == CStreamTester::GetTestData());

	CMemoryInputStream input(data);
	CStreamTester::TestRead(input);
}

TEST_CASE("Testing file streams without associated files")
{
	constexpr char BAD_PATH[] = "/inaccessible";

	REQUIRE_THROWS(CFileInputStream(BAD_PATH));
	REQUIRE_THROWS(CFileOutputStream(BAD_PATH));
}
