#pragma once
#include "ICanvas.hpp"

struct IDrawable
{
	virtual ~IDrawable() = default;

	virtual void Draw(ICanvas & canvas)const = 0;
};
