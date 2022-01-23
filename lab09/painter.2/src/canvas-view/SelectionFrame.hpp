#pragma once
#include "../drawing/types.hpp"

struct ICanvas;
struct IDrawingItem;

class SelectionFrame
{
public:
	void SetSelection(IDrawingItem const* item)
	{
		m_item = item;
	}

	Direction HitTest(Point const& point)const;

	void Draw(ICanvas & canvas)const;

private:
	IDrawingItem const* m_item = nullptr;
};
