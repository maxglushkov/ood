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
	constexpr static BoundingBox DEFAULT_SHAPE_BOUNDS{160, 120, 480, 360};

	History m_history;
	Drawing m_drawing{m_history, 640, 480};
	PainterWindow m_mainWindow{m_drawing};

	void InsertRectangle();

	void InsertTriangle();

	void InsertEllipse();

	void SetupMenu();

	template<typename T>
	void InsertShape();
};
