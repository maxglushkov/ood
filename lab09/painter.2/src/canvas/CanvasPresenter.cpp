#include <algorithm>
#include "../model/RectangularShape.hpp"
#include "CanvasPresenter.hpp"
#include "ICanvasPresenterItem.hpp"

CanvasPresenter::CanvasPresenter(View & view, Drawing & drawing)
	:m_view(view)
	,m_drawing(drawing)
{
	m_drawing.SelectionChangedSignal().connect(sigc::mem_fun(*this, &CanvasPresenter::OnSelectionChanged));
	m_drawing.ImageChangedSignal().connect(sigc::mem_fun(m_view, &View::Redraw));
}

void CanvasPresenter::MouseLeftButtonDown(Point const& pos)
{
	if (m_movingDir.none())
	{
		SetSelection(pos);
		if (!m_drawing.HasSelection())
		{
			return;
		}
		m_movingDir.set(Direction::Left).set(Direction::Top).set(Direction::Right).set(Direction::Bottom);
	}
	m_movingAnchor = pos;
}

void CanvasPresenter::MouseLeftButtonUp(Point const& pos)
{
	if (m_movingAnchor.has_value())
	{
		m_movingAnchor = std::nullopt;
		UpdateCursorType(pos);
	}
}

void CanvasPresenter::MouseMove(Point const& pos)
{
	if (m_movingAnchor.has_value())
	{
		const Point absPos{
			std::clamp(pos.x, 0.0, m_drawing.GetSize().width),
			std::clamp(pos.y, 0.0, m_drawing.GetSize().height)
		};
		const Point relPos = absPos - *m_movingAnchor;
		m_drawing.MoveSelectionBoundsRelative({
			m_movingDir[Direction::Left] ? relPos.x : 0.0,
			m_movingDir[Direction::Top] ? relPos.y : 0.0,
			m_movingDir[Direction::Right] ? relPos.x : 0.0,
			m_movingDir[Direction::Bottom] ? relPos.y : 0.0
		});
		*m_movingAnchor = absPos;
	}
	else
	{
		UpdateCursorType(pos);
	}
}

void CanvasPresenter::Draw(ICanvas & canvas)
{
	canvas.DrawRectangle({{}, m_drawing.GetSize()});
	canvas.SetColor(m_drawing.GetBackgroundColor());
	canvas.Fill();

	for (auto it = m_drawing.end(); it != m_drawing.begin();)
	{
		MakeCanvasPresenterItem(**--it)->Draw(canvas);
	}
	m_selectionFrame.Draw(canvas);
}

void CanvasPresenter::OnSelectionChanged(IDrawingItem const* item, bool imageChanged)
{
	m_selectionFrame.SetSelection(item);
	if (!imageChanged)
	{
		m_view.Redraw();
	}
}

void CanvasPresenter::InsertShape(IDrawingItem::Type type)
{
	constexpr static BoundingBox DEFAULT_SHAPE_BOUNDS{160, 120, 480, 360};
	m_drawing.PushFront(std::make_unique<RectangularShape>(type, DEFAULT_SHAPE_BOUNDS));
}

void CanvasPresenter::SetSelection(Point const& pos)
{
	auto it = m_drawing.begin();
	for (; it != m_drawing.end(); ++it)
	{
		if (MakeCanvasPresenterItem(**it)->HitTest(pos))
		{
			break;
		}
	}
	m_drawing.SetSelection(it);
}

void CanvasPresenter::UpdateCursorType(Point const& pos)
{
	const Direction movingDir = m_selectionFrame.HitTest(pos);
	if (movingDir != m_movingDir)
	{
		m_view.SetCursor(m_movingDir = movingDir);
	}
}
