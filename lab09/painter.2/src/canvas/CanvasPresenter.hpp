#pragma once
#include <sigc++/trackable.h>
#include "BoundsMovementState.hpp"
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

	void MouseLeftButtonDown(Point const& pos);

	void MouseLeftButtonUp(Point const& pos);

	void MouseMove(Point const& pos);

	void Draw(ICanvas & canvas);

private:
	View & m_view;
	Drawing & m_drawing;

	SelectionFrame m_selectionFrame;
	Direction m_movingDir;
	BoundsMovementState m_movementState;

	void OnSelectionChanged(IDrawingItem const* item, bool imageChanged);

	void SetSelection(Point const& pos);

	void UpdateCursorType(Point const& pos);
};
