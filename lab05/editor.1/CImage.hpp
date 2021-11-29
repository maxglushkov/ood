#pragma once
#include "CHistory.hpp"
#include "CSize.hpp"
#include "IImage.hpp"

class CImage: public IImage
{
public:
	CImage(CHistory & history, std::filesystem::path const& path, int width, int height)
		:m_history(history)
		,m_size(width, height)
		,m_path(path)
	{}

	std::filesystem::path GetPath()const override
	{
		return m_path;
	}

	int GetWidth()const override
	{
		return m_size.GetWidth();
	}

	int GetHeight()const override
	{
		return m_size.GetHeight();
	}

	void Resize(int width, int height)override;

private:
	CHistory & m_history;
	CSize m_size;
	const std::filesystem::path m_path;
};
