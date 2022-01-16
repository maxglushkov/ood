#pragma once
#include <memory>
#include <sigc++/signal.h>
#include "IDrawingItem.hpp"

typedef std::unique_ptr<IDrawingItem> IDrawingItemPtr;

class Drawing
{
public:
	typedef std::list<IDrawingItemPtr>::const_iterator Iterator;
	typedef sigc::signal<void(IDrawingItem const*, bool)> SignalSelectionChanged;
	typedef sigc::signal<void()> SignalImageChanged;

	Drawing(double width, double height, RGBAColor const& bgColor = Color::WHITE)
		:m_size{width, height}
		,m_bgColor(bgColor)
	{}

	Size const& GetSize()const
	{
		return m_size;
	}

	RGBAColor const& GetBackgroundColor()const
	{
		return m_bgColor;
	}

	bool HasSelection()const
	{
		return m_selection != m_items.cend();
	}

	Iterator begin()const
	{
		return m_items.cbegin();
	}

	Iterator end()const
	{
		return m_items.cend();
	}

	SignalSelectionChanged SelectionChangedSignal()const
	{
		return m_sigSelectionChanged;
	}

	SignalImageChanged ImageChangedSignal()const
	{
		return m_sigImageChanged;
	}

	void PushFront(IDrawingItemPtr && item);

	void SetSelection(Iterator it)
	{
		SetSelection(it, false);
	}

	void MoveSelectionBoundsRelative(BoundingBox const& delta);

	void DeleteSelection();

private:
	std::list<IDrawingItemPtr> m_items;
	Iterator m_selection = m_items.cend();
	Size m_size;
	RGBAColor m_bgColor;

	SignalSelectionChanged m_sigSelectionChanged;
	SignalImageChanged m_sigImageChanged;

	IDrawingItem * GetSelection();

	void SetSelection(Iterator it, bool imageChanged);
};
