#pragma once
#include <IDesigner.hpp>

struct Designer: public IDesigner
{
	CPictureDraft CreateDraft(std::istream & input)override
	{
		m_lastInput = &input;
		return CPictureDraft();
	}

	std::istream const* m_lastInput = nullptr;
};
