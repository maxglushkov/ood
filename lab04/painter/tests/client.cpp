#include <sstream>
#include "../../libpainter-tests/logging-canvas.hpp"
#include "../../libpainter-tests/shape.hpp"
#include "../CClient.hpp"
#include "designer.hpp"

TEST_CASE("Client visits designer")
{
	std::istringstream input;
	Designer designer;

	CClient::VisitDesigner(designer, input);

	REQUIRE(designer.m_lastInput == &input);
}

TEST_CASE("Client visits painter")
{
	CLoggingCanvas canvas;
	CPictureDraft draft;
	draft.AddShape(std::make_unique<Shape>(Color::Red));
	draft.AddShape(std::make_unique<Shape>(Color::Blue));

	CClient::VisitPainter(draft, canvas);

	canvas.Match({
		Color::Red,
		Color::Blue
	});
}
