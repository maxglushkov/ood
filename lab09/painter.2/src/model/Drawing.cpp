#include "Drawing.hpp"

void Drawing::PushFront(IDrawingItemPtr && item)
{
	m_items.push_front(std::move(item));
	SetSelection(m_items.cbegin(), true);
}

void Drawing::MoveSelectionBoundsRelative(BoundingBox const& delta)
{
	if (const auto item = GetSelection())
	{
		item->MoveBoundsRelative(delta);
		m_sigImageChanged();
	}
}

void Drawing::DeleteSelection()
{
	if (HasSelection())
	{
		m_items.erase(m_selection);
		SetSelection(m_items.cend(), true);
	}
}

IDrawingItem * Drawing::GetSelection()
{
	return HasSelection() ? m_selection->get() : nullptr;
}

void Drawing::SetSelection(Iterator it, bool imageChanged)
{
	if (it != m_selection)
	{
		m_selection = it;
		m_sigSelectionChanged(GetSelection(), imageChanged);
	}
	if (imageChanged)
	{
		m_sigImageChanged();
	}
}
