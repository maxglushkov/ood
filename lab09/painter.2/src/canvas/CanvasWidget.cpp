#include "CairoCanvas.hpp"
#include "CanvasWidget.hpp"

CanvasWidget::CanvasWidget(Drawing & drawing)
	:m_presenter(*this, drawing)
{
	set_size_request(int(drawing.GetSize().width), int(drawing.GetSize().height));
	add_events(Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);
}

Glib::RefPtr<Gio::SimpleActionGroup> CanvasWidget::BuildActionGroup()
{
	const auto group = Gio::SimpleActionGroup::create();
	group->add_action("edit_delete", sigc::mem_fun(m_presenter, &CanvasPresenter::DeleteSelection));
	group->add_action("insert_rectangle", sigc::mem_fun(m_presenter, &CanvasPresenter::InsertRectangle));
	group->add_action("insert_triangle", sigc::mem_fun(m_presenter, &CanvasPresenter::InsertTriangle));
	group->add_action("insert_ellipse", sigc::mem_fun(m_presenter, &CanvasPresenter::InsertEllipse));
	return group;
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
	m_presenter.Draw(canvas);
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
