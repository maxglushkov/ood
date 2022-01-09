#pragma once
#include <gtkmm/widget.h>
#include <optional>
#include "../model/Drawing.hpp"
#include "SelectionFrame.hpp"

class CanvasPresenter: public sigc::trackable
{
public:
	CanvasPresenter(Gtk::Widget & widget, Drawing & drawing);

	void DeleteSelection()
	{
		m_drawing.DeleteSelection();
	}

	void InsertRectangle();

	void InsertTriangle();

	void InsertEllipse();

	void MouseDown(GdkEventButton * event);

	void MouseUp(GdkEventButton * event);

	void MouseMove(GdkEventMotion * event);

	void Draw(Cairo::RefPtr<Cairo::Context> const& cr);

private:
	Gtk::Widget & m_widget;
	Drawing & m_drawing;

	SelectionFrame m_selectionFrame;
	Direction m_movingDir;
	std::optional<Point> m_movingAnchor;

	void OnSelectionChanged(IDrawingItem const* item, bool imageChanged);

	void OnImageChanged();

	void UpdateCursorType(Point const& point);
};
