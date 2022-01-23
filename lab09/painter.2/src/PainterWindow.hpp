#pragma once
#include <gtkmm/applicationwindow.h>
#include <gtkmm/scrolledwindow.h>
#include "canvas-view/CanvasWidget.hpp"

class PainterWindow: public Gtk::ApplicationWindow
{
public:
	explicit PainterWindow(Drawing & drawing);

private:
	Gtk::ScrolledWindow m_scrolledWindow;
	CanvasWidget m_canvas;
};
