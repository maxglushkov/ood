#pragma once
#include "IDesigner.hpp"
#include "IShapeFactory.hpp"

class CDesigner: public IDesigner
{
public:
	CDesigner(IShapeFactory & factory)
		:m_factory(factory)
	{}

	CPictureDraft CreateDraft(std::istream & input)override;

private:
	IShapeFactory & m_factory;
};
