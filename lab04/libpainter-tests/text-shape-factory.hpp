#pragma once
#include <IShapeFactory.hpp>
#include "text-shape.hpp"

struct TextShapeFactory: public IShapeFactory
{
	std::unique_ptr<CShape> CreateShape(std::string const& description)override
	{
		return std::make_unique<TextShape>(description);
	}
};
