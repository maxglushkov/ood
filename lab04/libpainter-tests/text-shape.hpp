#pragma once
#include <CShape.hpp>

struct TextShape: public CShape
{
	TextShape(std::string const& text)
		:CShape(Color::Black)
		,m_text(text)
	{}

	friend std::string const& GetShapeText(CShape const& shape);

private:
	std::string m_text;
};

inline std::string const& GetShapeText(CShape const& shape)
{
	return dynamic_cast<TextShape const&>(shape).m_text;
}
