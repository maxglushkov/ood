#include "PainterApplication.hpp"

void PainterApplication::on_startup()
{
	Gtk::Application::on_startup();

	SetupMenu();
}

void PainterApplication::on_activate()
{
	Gtk::Application::on_activate();

	add_window(m_mainWindow);
	m_mainWindow.show();
}

void PainterApplication::SetupMenu()
{
	const auto menuEdit = Gio::Menu::create();
	menuEdit->append("Delete", "canvas.edit_delete");
	set_accel_for_action("canvas.edit_delete", "Delete");

	const auto menuInsert = Gio::Menu::create();
	menuInsert->append("Rectangle", "canvas.insert_rectangle");
	menuInsert->append("Triangle", "canvas.insert_triangle");
	menuInsert->append("Ellipse", "canvas.insert_ellipse");

	const auto menu = Gio::Menu::create();
	menu->append_submenu("Edit", menuEdit);
	menu->append_submenu("Insert", menuInsert);
	set_menubar(menu);
}
