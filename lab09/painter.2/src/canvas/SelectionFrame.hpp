#pragma once
#include "../model/IDrawingItem.hpp"

class SelectionFrame: public IDrawable
{
public:
	void SetSelection(IDrawingItem const* item)
	{
		m_item = item;
	}

	Direction HitTest(Point const& point)const;

	void Draw(ICanvas & canvas)const override;

private:
	IDrawingItem const* m_item = nullptr;
};
