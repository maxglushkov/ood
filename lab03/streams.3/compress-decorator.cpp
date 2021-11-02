#include "compress-decorator.hpp"

void CDecompressInputStream::NextState()
{
	switch (m_state)
	{
		case State::Undetermined:
			if (GetStream().ReadBlock(&m_length, sizeof m_length))
			{
				m_state = State::StartSequence;
			}
			else
			{
				m_state = State::EndStream;
			}
			break;
		case State::StartSequence:
			m_byte = GetStream().ReadByte();
			m_state = State::InSequence;
			break;
		case State::InSequence:
			if (m_length < 0)
			{
				m_byte = GetStream().ReadByte();
				++m_length;
			}
			else if (m_length > 0)
			{
				--m_length;
			}
			else
			{
				m_state = State::Undetermined;
			}
			break;
		case State::EndStream:;
	}
}

void CCompressOutputStream::WriteByte(uint8_t data)
{
	switch (m_state)
	{
		case State::NoData:
			m_cache[m_length = 0] = data;
			m_state = State::SequenceLookup;
			break;
		case State::SequenceLookup:
			if (data == m_cache[m_length])
			{
				if (m_length)
				{
					--m_length;
					FlushRawSequence();
					m_cache[0] = data;
				}
				m_length = 1;
				m_state = State::InSequence;
			}
			else
			{
				if (m_length == MAX_RAW_LENGTH)
				{
					FlushRawSequence();
					m_length = 0;
				}
				else
				{
					++m_length;
				}
				m_cache[m_length] = data;
			}
			break;
		case State::InSequence:
			if (data == m_cache[0])
			{
				if (++m_length == MAX_RUN_LENGTH)
				{
					FlushRunSequence();
					m_state = State::NoData;
				}
			}
			else
			{
				FlushRunSequence();
				m_cache[m_length = 0] = data;
				m_state = State::SequenceLookup;
			}
	}
}

void CCompressOutputStream::Flush()
{
	switch (m_state)
	{
		case State::NoData:
			return;
		case State::SequenceLookup:
			FlushRawSequence();
			break;
		case State::InSequence:
			FlushRunSequence();
	}
	m_state = State::NoData;
}
