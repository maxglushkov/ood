#pragma once
#include <giomm/simpleactiongroup.h>
#include <gtkmm/drawingarea.h>
#include "CanvasPresenter.hpp"

class CanvasWidget: public Gtk::DrawingArea, private CanvasPresenter::View
{
public:
	explicit CanvasWidget(Drawing & drawing);

	Glib::RefPtr<Gio::SimpleActionGroup> BuildActionGroup();

protected:
	bool on_button_press_event(GdkEventButton * button_event)override;

	bool on_button_release_event(GdkEventButton * release_event)override;

	bool on_motion_notify_event(GdkEventMotion * motion_event)override;

	bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr)override;

private:
	CanvasPresenter m_presenter;

	void Redraw()override;

	void SetCursor(Direction dir)override;
};
