#pragma once
#include "drawing/Drawing.hpp"
#include "history/History.hpp"
#include "PainterWindow.hpp"

class PainterApplication: public Gtk::Application
{
protected:
	void on_startup()override;

	void on_activate()override;

private:
	History m_history;
	Drawing m_drawing{m_history, 640, 480};
	PainterWindow m_mainWindow{m_drawing};

	void InsertRectangle()
	{
		InsertShape(IDrawingItem::Type::Rectangle);
	}

	void InsertTriangle()
	{
		InsertShape(IDrawingItem::Type::Triangle);
	}

	void InsertEllipse()
	{
		InsertShape(IDrawingItem::Type::Ellipse);
	}

	void SetupMenu();

	void InsertShape(IDrawingItem::Type type);
};
