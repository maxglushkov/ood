#pragma once
#include "stream-decorator.hpp"

#ifndef I_AM_NOT_GOING_TO_PROTECT_ANY_DATA
#error "You don't yet know that you should never use these classes for data protection"
#endif

class CCrypt
{
public:
	typedef uint64_t KeyType;
	enum class Mode
	{
		Encryption,
		Decryption
	};

	CCrypt(KeyType key, Mode mode);

	uint8_t TransformByte(uint8_t byte)
	{
		return m_table[byte];
	}

	void TransformBlock(uint8_t * dest, uint8_t const* src, size_t size)
	{
		for (; size; ++dest, ++src, --size)
		{
			*dest = m_table[*src];
		}
	}

private:
	constexpr static size_t TABLE_LENGTH = 256;
	uint8_t m_table[TABLE_LENGTH];

	static void GenerateEncryptionTable(uint8_t * table, KeyType key);

	static void InvertTable(uint8_t * dstTable, uint8_t const* srcTable);
};

class CDecryptInputStream: public CInputStreamDecorator
{
public:
	CDecryptInputStream(IInputStreamPtr && stream, CCrypt::KeyType key)
		:CInputStreamDecorator(std::move(stream))
		,m_crypt(key, CCrypt::Mode::Decryption)
	{}

	bool IsEOF()const override
	{
		return GetStream().IsEOF();
	}

	uint8_t ReadByte()override
	{
		return m_crypt.TransformByte(GetStream().ReadByte());
	}

	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size)override
	{
		size = GetStream().ReadBlock(dstBuffer, size);
		const auto data = static_cast<uint8_t *>(dstBuffer);
		m_crypt.TransformBlock(data, data, size);
		return size;
	}

private:
	CCrypt m_crypt;
};

class CEncryptOutputStream: public COutputStreamDecorator
{
public:
	CEncryptOutputStream(IOutputStreamPtr && stream, CCrypt::KeyType key)
		:COutputStreamDecorator(std::move(stream))
		,m_crypt(key, CCrypt::Mode::Encryption)
	{}

	void WriteByte(uint8_t data)override
	{
		GetStream().WriteByte(m_crypt.TransformByte(data));
	}

	void WriteBlock(const void * srcData, std::streamsize size)override;

private:
	CCrypt m_crypt;
};
