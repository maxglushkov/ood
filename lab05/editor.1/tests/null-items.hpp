#pragma once
#include "../IImage.hpp"
#include "../IParagraph.hpp"

struct NullImage: public IImage
{
	std::filesystem::path GetPath()const override
	{
		return {};
	}

	int GetWidth()const override
	{
		return {};
	}

	int GetHeight()const override
	{
		return {};
	}

	void Resize(int, int)override
	{}
};

struct NullParagraph: public IParagraph
{
	std::string GetText()const override
	{
		return {};
	}

	void SetText(std::string const&)override
	{}
};
