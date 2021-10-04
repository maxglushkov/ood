#pragma once
#include <cstring>
#include <ios>
#include <vector>
#include "data-stream.hpp"

class CMemoryInputStream: public IInputDataStream
{
public:
	typedef std::vector<uint8_t> Container;

	CMemoryInputStream(Container const& data)
		:m_pos(data.begin())
		,m_end(data.end())
	{}

	bool IsEOF()const override
	{
		return m_pos == m_end;
	}

	uint8_t ReadByte()override
	{
		if (IsEOF())
		{
			throw std::ios::failure("CMemoryInputStream::ReadByte");
		}
		return *m_pos++;
	}

	std::streamsize ReadBlock(void * dstBuffer, std::streamsize size)override
	{
		size = std::max(size, 0L);
		size = std::min(size, m_end - m_pos);

		memcpy(dstBuffer, &*m_pos, size);
		m_pos += size;
		return size;
	}

private:
	Container::const_iterator m_pos, m_end;
};

class CMemoryOutputStream: public IOutputDataStream
{
public:
	typedef std::vector<uint8_t> Container;

	CMemoryOutputStream(Container & data)
		:m_data(data)
	{}

	void WriteByte(uint8_t data)override
	{
		try
		{
			m_data.push_back(data);
		}
		catch (std::exception const& e)
		{
			throw std::ios::failure(e.what());
		}
	}

	void WriteBlock(const void * srcData, std::streamsize size)override
	{
		try
		{
			const auto data = static_cast<uint8_t const*>(srcData);
			m_data.insert(m_data.end(), data, data + size);
		}
		catch (std::exception const& e)
		{
			throw std::ios::failure(e.what());
		}
	}

private:
	Container & m_data;
};
