#pragma once
#include <memory>
#include <sigc++/signal.h>
#include "IDrawingItem.hpp"

typedef std::unique_ptr<IDrawingItem> IDrawingItemPtr;

class Drawing: public IDrawable
{
public:
	Drawing(double width, double height)
		:m_size{width, height}
	{}

	Size const& GetSize()const
	{
		return m_size;
	}

	auto SelectionChangedSignal()const
	{
		return m_sigSelectionChanged;
	}

	auto ImageChangedSignal()const
	{
		return m_sigImageChanged;
	}

	void PushTop(IDrawingItemPtr && item);

	bool SetSelection(Point const& point);

	void MoveSelectionBoundsRelative(BoundingBox const& delta);

	void DeleteSelection();

	void Draw(ICanvas & canvas)const override;

private:
	std::list<IDrawingItemPtr> m_items;
	std::list<IDrawingItemPtr>::const_iterator m_selection = m_items.cend();
	Size m_size;

	sigc::signal<void(IDrawingItem const*, bool)> m_sigSelectionChanged;
	sigc::signal<void()> m_sigImageChanged;

	bool HasSelection()const;

	IDrawingItem * GetSelection();

	void SetSelection(std::list<IDrawingItemPtr>::const_iterator it, bool imageChanged);
};
