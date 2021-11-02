#pragma once
#include <ios>
#include "stream-decorator.hpp"

class CDecompressInputStream: public CInputStreamDecorator
{
public:
	CDecompressInputStream(IInputStreamPtr && stream)
		:CInputStreamDecorator(std::move(stream))
	{}

	bool IsEOF()const override
	{
		return m_state == State::EndStream;
	}

	uint8_t ReadByte()override
	{
		for (;;)
		{
			NextState();
			switch (m_state)
			{
				case State::Undetermined:
				case State::StartSequence:
					break;
				case State::InSequence:
					return m_byte;
				case State::EndStream:
					throw std::ios::failure("CDecompressInputStream::ReadByte");
			}
		}
	}

	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size)override
	{
		auto data = static_cast<uint8_t *>(dstBuffer);
		for (std::streamsize pos = 0; pos < size;)
		{
			NextState();
			switch (m_state)
			{
				case State::Undetermined:
				case State::StartSequence:
					break;
				case State::InSequence:
					data[pos++] = m_byte;
					break;
				case State::EndStream:
					return pos;
			}
		}
		return size;
	}

private:
	enum class State: uint8_t
	{
		Undetermined,
		StartSequence,
		InSequence,
		EndStream
	};
	State m_state = State::Undetermined;
	int8_t m_length;
	uint8_t m_byte;

	void NextState();
};

class CCompressOutputStream: public COutputStreamDecorator
{
public:
	CCompressOutputStream(IOutputStreamPtr && stream)
		:COutputStreamDecorator(std::move(stream))
	{}

	~CCompressOutputStream()override
	{
		try
		{
			Flush();
		}
		catch (...)
		{}
	}

	void WriteByte(uint8_t data)override;

	void WriteBlock(const void * srcData, std::streamsize size)override
	{
		for (auto data = static_cast<uint8_t const*>(srcData); size; ++data, --size)
		{
			WriteByte(*data);
		}
	}

private:
	enum class State: uint8_t
	{
		NoData,
		SequenceLookup,
		InSequence
	};
	constexpr static uint8_t MAX_RAW_LENGTH = -INT8_MIN;
	constexpr static uint8_t MAX_RUN_LENGTH = INT8_MAX;

	State m_state = State::NoData;
	uint8_t m_length;
	uint8_t m_cache[MAX_RAW_LENGTH + 1];

	void Flush();

	void FlushRawSequence()
	{
		GetStream().WriteByte(-m_length);
		GetStream().WriteBlock(m_cache, m_length + 1);
	}

	void FlushRunSequence()
	{
		GetStream().WriteByte(m_length);
		GetStream().WriteByte(m_cache[0]);
	}
};
