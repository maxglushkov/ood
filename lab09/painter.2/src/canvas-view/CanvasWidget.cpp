#include "../canvas/CairoCanvas.hpp"
#include "../canvas/CanvasPainter.hpp"
#include "CanvasWidget.hpp"

CanvasWidget::CanvasWidget(Drawing & drawing)
	:m_presenter(*this, drawing)
{
	set_size_request(int(m_presenter.GetDrawingSize().width), int(m_presenter.GetDrawingSize().height));
	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

bool CanvasWidget::on_button_press_event(GdkEventButton * button_event)
{
	if (button_event->button == 1)
	{
		m_presenter.MouseLeftButtonDown({button_event->x, button_event->y});
		return true;
	}
	return false;
}

bool CanvasWidget::on_button_release_event(GdkEventButton * release_event)
{
	if (release_event->button == 1)
	{
		m_presenter.MouseLeftButtonUp({release_event->x, release_event->y});
		return true;
	}
	return false;
}

bool CanvasWidget::on_motion_notify_event(GdkEventMotion * motion_event)
{
	m_presenter.MouseMove({motion_event->x, motion_event->y});
	return true;
}

bool CanvasWidget::on_draw(Cairo::RefPtr<Cairo::Context> const& cr)
{
	CairoCanvas canvas(cr);
	canvas.DrawRectangle({{}, m_presenter.GetDrawingSize()});
	canvas.SetColor(m_presenter.GetDrawingBackgroundColor());
	canvas.Fill();

	CanvasPainter painter(canvas);
	m_presenter.AcceptFrontwardVisitor(painter);

	m_presenter.GetSelectionFrame().Draw(canvas);
	return true;
}

void CanvasWidget::Redraw()
{
	if (const auto window = get_window())
	{
		window->invalidate(false);
	}
}

void CanvasWidget::SetCursor(Direction dir)
{
	if (const auto window = get_window())
	{
		window->set_cursor(Gdk::Cursor::create(
			dir[Direction::Top] ?
				dir[Direction::Left] ? Gdk::TOP_LEFT_CORNER :
				dir[Direction::Right] ? Gdk::TOP_RIGHT_CORNER :
				Gdk::TOP_SIDE :
			dir[Direction::Bottom] ?
				dir[Direction::Left] ? Gdk::BOTTOM_LEFT_CORNER :
				dir[Direction::Right] ? Gdk::BOTTOM_RIGHT_CORNER :
				Gdk::BOTTOM_SIDE :
			dir[Direction::Left] ? Gdk::LEFT_SIDE :
			dir[Direction::Right] ? Gdk::RIGHT_SIDE :
			Gdk::ARROW
		));
	}
}
