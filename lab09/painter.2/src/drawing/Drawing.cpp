#include "../history/IHistory.hpp"
#include "../history/ListCommand.hpp"
#include "BoundsMovement.hpp"
#include "Drawing.hpp"

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
	SetSelection(m_items.begin(), true);
}

void Drawing::BeginSelectionBoundsMovement()
{
	m_history.Lock();

	*m_selection = std::make_unique<BoundsMovement>(std::move(*m_selection));
	m_sigSelectionChanged(GetSelection(), false);
}

void Drawing::SetSelectionBounds(BoundingBox const& bounds)
{
	(*m_selection)->SetBoundingBox(nullptr, bounds);
	m_sigImageChanged();
}

void Drawing::EndSelectionBoundsMovement()
{
	m_history.Unlock();

	const auto boundsMovement = m_selection->get();
	boundsMovement->GetInner()->SetBoundingBox(&m_history, boundsMovement->GetBoundingBox());
	*m_selection = boundsMovement->IntoInner();
	m_sigSelectionChanged(GetSelection(), false);
}

void Drawing::DeleteSelection()
{
	if (HasSelection() && !(*m_selection)->GetInner())
	{
		m_history.Do(std::make_unique<ListCommand<IDrawingItemPtr>>(m_items, m_selection));
		SetSelection(m_items.end(), true);
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
	SetSelection(m_items.end(), true);
}
