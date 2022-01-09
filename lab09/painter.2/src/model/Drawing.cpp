#include "Drawing.hpp"

constexpr static RGBAColor BACKGROUND_COLOR(1.0, 1.0, 1.0);

void Drawing::PushTop(IDrawingItemPtr && item)
{
	m_items.push_front(std::move(item));
	SetSelection(m_items.cbegin(), true);
}

bool Drawing::SetSelection(Point const& point)
{
	auto it = m_items.cbegin();
	for (; it != m_items.cend(); ++it)
	{
		if ((*it)->HitTest(point))
		{
			break;
		}
	}
	SetSelection(it, false);
	return HasSelection();
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

void Drawing::Draw(ICanvas & canvas)const
{
	canvas.DrawRectangle({0, 0, m_size.width, m_size.height});
	canvas.SetColor(BACKGROUND_COLOR);
	canvas.Fill();

	for (auto rit = m_items.crbegin(); rit != m_items.crend(); ++rit)
	{
		(*rit)->Draw(canvas);
	}
}

bool Drawing::HasSelection()const
{
	return m_selection != m_items.cend();
}

IDrawingItem * Drawing::GetSelection()
{
	return HasSelection() ? m_selection->get() : nullptr;
}

void Drawing::SetSelection(std::list<IDrawingItemPtr>::const_iterator it, bool imageChanged)
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
