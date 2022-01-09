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
