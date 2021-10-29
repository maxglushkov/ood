#include <catch2/catch.hpp>
#include "stream-tester.hpp"

void CStreamTester::TestRead(IInputDataStream & input)
{
	uint8_t block[sizeof PHRASE];
	REQUIRE(input.ReadBlock(block, sizeof block) == sizeof block);
	REQUIRE(std::equal(block, std::end(block), PHRASE));
	REQUIRE(input.ReadByte() == 0);
	REQUIRE_THROWS(input.ReadByte());
	REQUIRE(input.ReadBlock(block, sizeof block) == 0);
}

void CStreamTester::TestWrite(IOutputDataStream & output)
{
	output.WriteBlock(PHRASE, sizeof PHRASE);
	output.WriteByte(0);
}

std::vector<uint8_t> CStreamTester::GetTestData()
{
	std::vector<uint8_t> data(PHRASE, std::end(PHRASE));
	data.push_back(0);
	return data;
}

size_t CStreamTester::GetTestDataSize()
{
	return sizeof PHRASE + 1;
}
