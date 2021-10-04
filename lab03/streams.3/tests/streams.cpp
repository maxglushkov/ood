#include <catch2/catch.hpp>
#include <filesystem>
#include "../file-stream.hpp"
#include "../memory-stream.hpp"

class CStreamTester
{
public:
	static void TestRead(IInputDataStream & input)
	{
		uint8_t block[sizeof PHRASE];
		REQUIRE(input.ReadBlock(block, sizeof block) == sizeof block);
		REQUIRE(memcmp(block, PHRASE, sizeof PHRASE) == 0);
		REQUIRE(input.ReadByte() == 0);
		REQUIRE_THROWS(input.ReadByte());
		REQUIRE(input.ReadBlock(block, sizeof block) == 0);
	}

	static void TestWrite(IOutputDataStream & output)
	{
		output.WriteBlock(PHRASE, sizeof PHRASE);
		output.WriteByte(0);
	}

	static std::vector<uint8_t> GetTestData()
	{
		std::vector<uint8_t> data(PHRASE, PHRASE + sizeof PHRASE);
		data.push_back(0);
		return data;
	}

	static size_t GetTestDataSize()
	{
		return sizeof PHRASE + 1;
	}

private:
	constexpr static uint8_t PHRASE[] = {0xde, 0xad, 0xbe, 0xef};
};

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
