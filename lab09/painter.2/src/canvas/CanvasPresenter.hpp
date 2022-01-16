#pragma once
#include <optional>
#include "../model/Drawing.hpp"
#include "SelectionFrame.hpp"

class CanvasPresenter: public sigc::trackable
{
public:
	struct View: virtual public sigc::trackable
	{
		virtual ~View() = default;

		virtual void Redraw() = 0;

		virtual void SetCursor(Direction dir) = 0;
	};

	CanvasPresenter(View & view, Drawing & drawing);

	void DeleteSelection()
	{
		m_drawing.DeleteSelection();
	}

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

	void MouseLeftButtonDown(Point const& pos);

	void MouseLeftButtonUp(Point const& pos);

	void MouseMove(Point const& pos);

	void Draw(ICanvas & canvas);

private:
	View & m_view;
	Drawing & m_drawing;

	SelectionFrame m_selectionFrame;
	Direction m_movingDir;
	std::optional<Point> m_movingAnchor;

	void OnSelectionChanged(IDrawingItem const* item, bool imageChanged);

	void InsertShape(IDrawingItem::Type type);

	void SetSelection(Point const& pos);

	void UpdateCursorType(Point const& pos);
};
