#pragma once
#include <memory>
#include "CShape.hpp"

struct IShapeFactory
{
	virtual ~IShapeFactory() = default;

	virtual std::unique_ptr<CShape> CreateShape(std::string const& description) = 0;
};
