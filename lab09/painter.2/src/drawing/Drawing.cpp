#include <stdexcept>
#include "../history/IHistory.hpp"
#include "../history/ListCommand.hpp"
#include "Drawing.hpp"

constexpr static char ERROR_NO_SELECTION[] = "drawing has no selection";

Drawing::Drawing(IHistory & history, double width, double height, RGBAColor const& bgColor)
	:m_history(history)
	,m_size{width, height}
	,m_bgColor(bgColor)
{
	m_history.UndoneRedoneSignal().connect(sigc::mem_fun(*this, &Drawing::OnUndoneRedone));
}

void Drawing::PushFront(IDrawingItemPtr && item)
{
	m_history.Do(std::make_unique<ListCommand<IDrawingItemPtr>>(m_items, m_items.cbegin(), std::move(item)));
	SetSelection(m_items.cbegin(), true);
}

void Drawing::BeginSelectionBoundsMovement()
{
	if (!HasSelection())
	{
		throw std::logic_error(ERROR_NO_SELECTION);
	}

	(*m_selection)->BeginBoundingBoxOperation(m_history);
}

void Drawing::SetSelectionBounds(BoundingBox const& bounds)
{
	if (HasSelection())
	{
		(*m_selection)->SetBoundingBox(bounds);
		m_sigImageChanged();
	}
}

void Drawing::EndSelectionBoundsMovement()
{
	m_history.Commit();
}

void Drawing::DeleteSelection()
{
	if (HasSelection() && !m_history.IsLocked())
	{
		m_history.Do(std::make_unique<ListCommand<IDrawingItemPtr>>(m_items, m_selection));
		SetSelection(m_items.cend(), true);
	}
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

void Drawing::OnUndoneRedone()
{
	SetSelection(m_items.cend(), true);
}
