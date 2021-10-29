#pragma once
#include <memory>
#include "data-stream.hpp"

typedef std::unique_ptr<IInputDataStream> IInputStreamPtr;
typedef std::unique_ptr<IOutputDataStream> IOutputStreamPtr;

class CInputStreamDecorator: public IInputDataStream
{
protected:
	CInputStreamDecorator(IInputStreamPtr && stream)
		:m_stream(std::move(stream))
	{}

	IInputDataStream & GetStream()
	{
		return *m_stream;
	}

	IInputDataStream const& GetStream()const
	{
		return *m_stream;
	}

private:
	IInputStreamPtr m_stream;
};

class COutputStreamDecorator: public IOutputDataStream
{
protected:
	COutputStreamDecorator(IOutputStreamPtr && stream)
		:m_stream(std::move(stream))
	{}

	IOutputDataStream & GetStream()
	{
		return *m_stream;
	}

private:
	IOutputStreamPtr m_stream;
};
