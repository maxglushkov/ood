#pragma once
#include <memory>
#include <sigc++/signal.h>
#include "IDrawingItem.hpp"

typedef std::unique_ptr<IDrawingItem> IDrawingItemPtr;

class Drawing: virtual public sigc::trackable
{
public:
	typedef std::list<IDrawingItemPtr>::const_iterator Iterator;
	typedef sigc::signal<void(IDrawingItem const*, bool)> SignalSelectionChanged;
	typedef sigc::signal<void()> SignalImageChanged;

	Drawing(IHistory & history, double width, double height, RGBAColor const& bgColor = Color::WHITE);

	Size const& GetSize()const
	{
		return m_size;
	}

	RGBAColor const& GetBackgroundColor()const
	{
		return m_bgColor;
	}

	IDrawingItem const* GetSelection()const
	{
		return HasSelection() ? m_selection->get() : nullptr;
	}

	bool HasSelection()const
	{
		return m_selection != m_items.cend();
	}

	Iterator begin()
	{
		return m_items.cbegin();
	}

	Iterator end()
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

	void BeginSelectionBoundsMovement();

	void SetSelectionBounds(BoundingBox const& bounds);

	void EndSelectionBoundsMovement();

	void DeleteSelection();

private:
	IHistory & m_history;

	std::list<IDrawingItemPtr> m_items;
	Iterator m_selection = m_items.cend();
	Size m_size;
	RGBAColor m_bgColor;

	SignalSelectionChanged m_sigSelectionChanged;
	SignalImageChanged m_sigImageChanged;

	void OnUndoneRedone();

	void SetSelection(Iterator it, bool imageChanged);
};
