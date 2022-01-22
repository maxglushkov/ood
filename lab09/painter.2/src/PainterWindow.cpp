#include "PainterWindow.hpp"

PainterWindow::PainterWindow(Drawing & drawing)
	:m_canvas(drawing)
{
	set_title("Painter");
	set_default_size(800, 600);

	m_canvas.set_halign(Gtk::ALIGN_START);
	m_canvas.set_valign(Gtk::ALIGN_START);
	m_scrolledWindow.add(m_canvas);
	add(m_scrolledWindow);
	m_canvas.show();
	m_scrolledWindow.show();
}
