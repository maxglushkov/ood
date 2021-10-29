#include <catch2/catch.hpp>
#include "stream-tester.hpp"
#include "../crypt-decorator.hpp"
#include "../memory-stream.hpp"

constexpr static CCrypt::KeyType KEY = 0xc01d;
constexpr static uint8_t SALT[] = {0x3a, 0x17};

TEST_CASE("Checking whether data does not change after encryption+decryption")
{
	std::vector<uint8_t> data;
	{
		CEncryptOutputStream output(std::make_unique<CMemoryOutputStream>(data), KEY);
		CStreamTester::TestWrite(output);
	}
	{
		CDecryptInputStream input(std::make_unique<CMemoryInputStream>(data), KEY);
		CStreamTester::TestRead(input);
	}
}

static void TestReadSalted(std::vector<uint8_t> const& data)
{
	CDecryptInputStream input(std::make_unique<CMemoryInputStream>(data), KEY);
	REQUIRE(input.ReadByte() == SALT[0]);
	REQUIRE(input.ReadByte() == SALT[1]);
	CStreamTester::TestRead(input);
}

TEST_CASE("Checking whether encryption streams does not affect each other")
{
	std::vector<uint8_t> data1, data2;
	{
		CEncryptOutputStream output1(std::make_unique<CMemoryOutputStream>(data1), KEY);
		CEncryptOutputStream output2(std::make_unique<CMemoryOutputStream>(data2), KEY);
		output1.WriteByte(SALT[0]);
		output2.WriteByte(SALT[0]);
		output2.WriteByte(SALT[1]);
		output1.WriteByte(SALT[1]);
		CStreamTester::TestWrite(output2);
		CStreamTester::TestWrite(output1);
	}
	TestReadSalted(data1);
	TestReadSalted(data2);
}
