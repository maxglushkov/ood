#pragma once
#include "CPictureDraft.hpp"

class CPainter
{
public:
	static void DrawPicture(CPictureDraft const& draft, ICanvas & canvas)
	{
		for (auto & shape: draft)
		{
			shape.Draw(canvas);
		}
	}
};
