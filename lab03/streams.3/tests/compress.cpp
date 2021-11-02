#include <catch2/catch.hpp>
#include "stream-tester.hpp"
#include "../compress-decorator.hpp"
#include "../memory-stream.hpp"

TEST_CASE("Checking whether data does not change after compression+decompression")
{
	std::vector<uint8_t> data;
	{
		CCompressOutputStream output(std::make_unique<CMemoryOutputStream>(data));
		CStreamTester::TestWrite(output);
	}
	{
		CDecompressInputStream input(std::make_unique<CMemoryInputStream>(data));
		CStreamTester::TestRead(input);
	}
}

TEST_CASE("Checking how corrupted streams are decompressed")
{
	std::vector<uint8_t> data;
	uint8_t bad;
	{
		data = {uint8_t(-5), 'H', 'e', 'l', 'l', 'o'};
		CDecompressInputStream input(std::make_unique<CMemoryInputStream>(data));
		for (size_t i = 0; ++i < data.size();)
		{
			REQUIRE(input.ReadByte() == data[i]);
		}
		REQUIRE_THROWS(input.ReadBlock(&bad, sizeof bad));
	}
	{
		data = {0};
		CDecompressInputStream input(std::make_unique<CMemoryInputStream>(data));
		REQUIRE_THROWS(input.ReadBlock(&bad, sizeof bad));
	}
}

static void TestCompression(char const* data, std::initializer_list<uint8_t> const& zData)
{
	std::vector<uint8_t> result;
	{
		CCompressOutputStream output(std::make_unique<CMemoryOutputStream>(result));
		output.WriteBlock(data, strlen(data));
	}
	REQUIRE(std::equal(result.begin(), result.end(), zData.begin(), zData.end()));
}

TEST_CASE("Checking whether compression works as intended")
{
	TestCompression("WWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW", {8, 'W', 2, 'B', 23, 'W', 0, 'B', 13, 'W'});
	TestCompression("ABCABCABCDDDFFFFFF", {uint8_t(-8), 'A', 'B', 'C', 'A', 'B', 'C', 'A', 'B', 'C', 2, 'D', 5, 'F'});
	TestCompression(
		"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\
		abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabc\n\
		abcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabcdefabc",
		{127, 'A', 0, '\n', 1, '\t', 127, 'A', uint8_t(-1), 'A', '\n', 1, '\t', uint8_t(-128), 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
		'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f',
		'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
		'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f',
		'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
		'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 0, '\n', 1, '\t', uint8_t(-128), 'a', 'b', 'c', 'd', 'e', 'f',
		'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
		'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f',
		'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c',
		'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f',
		'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c', 'd', 'e', 'f', 'a', 'b', 'c'}
	);
}
