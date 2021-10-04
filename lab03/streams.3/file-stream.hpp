#pragma once
#include <fstream>
#include "data-stream.hpp"

class CFileInputStream: public IInputDataStream
{
public:
	CFileInputStream(std::string const& filename)
		:m_stream(filename, std::ios::in | std::ios::binary)
	{
		m_stream.exceptions(std::ios::failbit);
		m_stream.exceptions(std::ios::badbit);
	}

	bool IsEOF()const override
	{
		return m_stream.eof();
	}

	uint8_t ReadByte()override
	{
		const uint8_t got = m_stream.get();
		if (IsEOF())
		{
			throw std::ios::failure("CFileInputStream::ReadByte");
		}
		return got;
	}

	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size)override
	{
		m_stream.read(static_cast<char *>(dstBuffer), size);
		return m_stream.gcount();
	}

private:
	std::ifstream m_stream;
};

class CFileOutputStream: public IOutputDataStream
{
public:
	CFileOutputStream(std::string const& filename)
		:m_stream(filename, std::ios::out | std::ios::binary)
	{
		m_stream.exceptions(std::ios::failbit);
		m_stream.exceptions(std::ios::badbit);
	}

	void WriteByte(uint8_t data)override
	{
		m_stream.put(data);
	}

	void WriteBlock(const void * srcData, std::streamsize size)override
	{
		m_stream.write(static_cast<char const*>(srcData), size);
	}

private:
	std::ofstream m_stream;
};
