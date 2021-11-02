#include <CPainter.hpp>
#include "logging-canvas.hpp"
#include "shape.hpp"

TEST_CASE("Drawing empty draft")
{
	CLoggingCanvas canvas;

	CPainter::DrawPicture(CPictureDraft(), canvas);

	canvas.Match({});
}

TEST_CASE("Drawing draft with shapes")
{
	CLoggingCanvas canvas;
	CPictureDraft draft;
	draft.AddShape(std::make_unique<Shape>(Color::Yellow));
	draft.AddShape(std::make_unique<Shape>(Color::Black));
	draft.AddShape(std::make_unique<Shape>(Color::Pink));

	CPainter::DrawPicture(draft, canvas);

	canvas.Match({
		Color::Yellow,
		Color::Black,
		Color::Pink
	});
}
