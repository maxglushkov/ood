#pragma once
#include "IShapeFactory.hpp"

class CShapeFactory: public IShapeFactory
{
public:
	std::unique_ptr<CShape> CreateShape(std::string const& description)override;
};
