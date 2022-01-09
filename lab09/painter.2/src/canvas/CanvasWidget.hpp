#pragma once
#include <giomm/simpleactiongroup.h>
#include <gtkmm/drawingarea.h>
#include "CanvasPresenter.hpp"

class CanvasWidget: public Gtk::DrawingArea
{
public:
	explicit CanvasWidget(Drawing & drawing);

	Glib::RefPtr<Gio::SimpleActionGroup> BuildActionGroup();

protected:
	bool on_button_press_event(GdkEventButton * button_event)override
	{
		m_presenter.MouseDown(button_event);
		return true;
	}

	bool on_button_release_event(GdkEventButton * release_event)override
	{
		m_presenter.MouseUp(release_event);
		return true;
	}

	bool on_motion_notify_event(GdkEventMotion * motion_event)override
	{
		m_presenter.MouseMove(motion_event);
		return true;
	}

	bool on_draw(Cairo::RefPtr<Cairo::Context> const& cr)override
	{
		m_presenter.Draw(cr);
		return true;
	}

private:
	CanvasPresenter m_presenter;
};
