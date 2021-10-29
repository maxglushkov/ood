#include <algorithm>
#include <ios>
#include <random>
#include "crypt-decorator.hpp"

CCrypt::CCrypt(KeyType key, Mode mode)
{
	if (mode == Mode::Encryption)
	{
		GenerateEncryptionTable(m_table, key);
	}
	else
	{
		uint8_t table[TABLE_LENGTH];
		GenerateEncryptionTable(table, key);
		InvertTable(m_table, table);
	}
}

void CCrypt::GenerateEncryptionTable(uint8_t * table, KeyType key)
{
	for (size_t i = 0; i < TABLE_LENGTH; ++i)
	{
		table[i] = i;
	}
	std::shuffle(table, table + TABLE_LENGTH, std::mt19937(key));
}

void CCrypt::InvertTable(uint8_t * dstTable, uint8_t const* srcTable)
{
	for (size_t i = 0; i < TABLE_LENGTH; ++i)
	{
		dstTable[srcTable[i]] = i;
	}
}

void CEncryptOutputStream::WriteBlock(const void * srcData, std::streamsize size)
{
	std::vector<uint8_t> data;
	try
	{
		data.resize(size);
	}
	catch (std::exception const& e)
	{
		throw std::ios::failure(e.what());
	}
	m_crypt.TransformBlock(data.data(), static_cast<uint8_t const*>(srcData), size);
	GetStream().WriteBlock(data.data(), size);
}
