#include "CairoCanvas.hpp"
#include "CanvasPresenter.hpp"
#include "../model/Ellipse.hpp"
#include "../model/Rectangle.hpp"
#include "../model/Triangle.hpp"

constexpr static BoundingBox DEFAULT_SHAPE_BOUNDS{160, 120, 480, 360};

CanvasPresenter::CanvasPresenter(Gtk::Widget & widget, Drawing & drawing)
	:m_widget(widget)
	,m_drawing(drawing)
{
	m_drawing.SelectionChangedSignal().connect(sigc::mem_fun(*this, &CanvasPresenter::OnSelectionChanged));
	m_drawing.ImageChangedSignal().connect(sigc::mem_fun(*this, &CanvasPresenter::OnImageChanged));
}

void CanvasPresenter::InsertRectangle()
{
	m_drawing.PushTop(std::make_unique<Rectangle>(DEFAULT_SHAPE_BOUNDS));
}

void CanvasPresenter::InsertTriangle()
{
	m_drawing.PushTop(std::make_unique<Triangle>(DEFAULT_SHAPE_BOUNDS));
}

void CanvasPresenter::InsertEllipse()
{
	m_drawing.PushTop(std::make_unique<Ellipse>(DEFAULT_SHAPE_BOUNDS));
}

void CanvasPresenter::MouseDown(GdkEventButton * event)
{
	if (event->button == 1)
	{
		if (m_movingDir.none())
		{
			if (!m_drawing.SetSelection({event->x, event->y}))
			{
				return;
			}
			m_movingDir.set(Direction::Left).set(Direction::Top).set(Direction::Right).set(Direction::Bottom);
		}
		m_movingAnchor = {event->x, event->y};
	}
}

void CanvasPresenter::MouseUp(GdkEventButton * event)
{
	if (event->button == 1)
	{
		m_movingAnchor = std::nullopt;
		UpdateCursorType({event->x, event->y});
	}
}

void CanvasPresenter::MouseMove(GdkEventMotion * event)
{
	if (m_movingAnchor)
	{
		const Point absPos{
			std::clamp(event->x, 0.0, m_drawing.GetSize().width),
			std::clamp(event->y, 0.0, m_drawing.GetSize().height)
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
		UpdateCursorType({event->x, event->y});
	}
}

void CanvasPresenter::Draw(Cairo::RefPtr<Cairo::Context> const& cr)
{
	CairoCanvas canvas(cr);
	m_drawing.Draw(canvas);
	m_selectionFrame.Draw(canvas);
}

void CanvasPresenter::OnSelectionChanged(IDrawingItem const* item, bool imageChanged)
{
	m_selectionFrame.SetSelection(item);
	if (!imageChanged)
	{
		OnImageChanged();
	}
}

void CanvasPresenter::OnImageChanged()
{
	if (const auto window = m_widget.get_window())
	{
		window->invalidate(false);
	}
}

void CanvasPresenter::UpdateCursorType(Point const& point)
{
	if (const auto window = m_widget.get_window())
	{
		const Direction movingDir = m_selectionFrame.HitTest(point);
		if (movingDir == m_movingDir)
		{
			return;
		}
		m_movingDir = movingDir;

		window->set_cursor(Gdk::Cursor::create(
			movingDir[Direction::Top] ?
				movingDir[Direction::Left] ? Gdk::TOP_LEFT_CORNER :
				movingDir[Direction::Right] ? Gdk::TOP_RIGHT_CORNER :
				Gdk::TOP_SIDE :
			movingDir[Direction::Bottom] ?
				movingDir[Direction::Left] ? Gdk::BOTTOM_LEFT_CORNER :
				movingDir[Direction::Right] ? Gdk::BOTTOM_RIGHT_CORNER :
				Gdk::BOTTOM_SIDE :
			movingDir[Direction::Left] ? Gdk::LEFT_SIDE :
			movingDir[Direction::Right] ? Gdk::RIGHT_SIDE :
			Gdk::ARROW
		));
	}
}
