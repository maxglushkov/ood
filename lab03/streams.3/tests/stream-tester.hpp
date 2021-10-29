#pragma once
#include <vector>
#include "../data-stream.hpp"

class CStreamTester
{
public:
	static void TestRead(IInputDataStream & input);

	static void TestWrite(IOutputDataStream & output);

	static std::vector<uint8_t> GetTestData();

	static size_t GetTestDataSize();

private:
	constexpr static uint8_t PHRASE[] = {0xde, 0xad, 0xbe, 0xef};
};
