#pragma once
#include <stdexcept>

class CSize
{
public:
	constexpr static int MIN_SIZE = 1;
	constexpr static int MAX_SIZE = 10000;

	CSize(int width, int height)
		:m_width(CheckDimension(width))
		,m_height(CheckDimension(height))
	{}

	int GetWidth()const
	{
		return m_width;
	}

	int GetHeight()const
	{
		return m_height;
	}

private:
	int m_width, m_height;

	int CheckDimension(int dimension)
	{
		if (dimension < MIN_SIZE || dimension > MAX_SIZE)
		{
			throw std::invalid_argument("width and height should be in range [1; 10000]");
		}
		return dimension;
	}
};
