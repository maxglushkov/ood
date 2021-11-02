#pragma once
#include "CPictureDraft.hpp"

struct IDesigner
{
	virtual ~IDesigner() = default;

	virtual CPictureDraft CreateDraft(std::istream & input) = 0;
};
