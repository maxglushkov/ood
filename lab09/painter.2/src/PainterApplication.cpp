#include "drawing/RectangularShape.hpp"
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
	menuEdit->append("Undo", "app.edit_undo");
	menuEdit->append("Redo", "app.edit_redo");
	menuEdit->append("Delete", "app.edit_delete");

	const auto menuInsert = Gio::Menu::create();
	menuInsert->append("Rectangle", "app.insert_rectangle");
	menuInsert->append("Triangle", "app.insert_triangle");
	menuInsert->append("Ellipse", "app.insert_ellipse");

	const auto menu = Gio::Menu::create();
	menu->append_submenu("Edit", menuEdit);
	menu->append_submenu("Insert", menuInsert);
	set_menubar(menu);

	set_accel_for_action("app.edit_undo", "<Primary>z");
	set_accel_for_action("app.edit_redo", "<Primary>y");
	set_accel_for_action("app.edit_delete", "Delete");

	add_action("edit_undo", sigc::mem_fun(m_history, &History::Undo));
	add_action("edit_redo", sigc::mem_fun(m_history, &History::Redo));
	add_action("edit_delete", sigc::mem_fun(m_drawing, &Drawing::DeleteSelection));
	add_action("insert_rectangle", sigc::mem_fun(*this, &PainterApplication::InsertRectangle));
	add_action("insert_triangle", sigc::mem_fun(*this, &PainterApplication::InsertTriangle));
	add_action("insert_ellipse", sigc::mem_fun(*this, &PainterApplication::InsertEllipse));
}

void PainterApplication::InsertShape(IDrawingItem::Type type)
{
	constexpr static BoundingBox DEFAULT_SHAPE_BOUNDS{160, 120, 480, 360};
	m_drawing.PushFront(std::make_unique<RectangularShape>(type, DEFAULT_SHAPE_BOUNDS));
}
