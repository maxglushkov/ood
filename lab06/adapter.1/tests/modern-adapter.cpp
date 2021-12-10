#include <catch2/catch.hpp>
#include <sstream>
#include "../modern-adapter.hpp"
using app::CModernGraphicsCanvas, modern_graphics_lib::CModernGraphicsRenderer;

const static modern_graphics_lib::CPoint FIRST(-10, 20), SECOND(10, -20);

TEST_CASE("CModernGraphicsCanvas: creating object draws nothing")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);

	CModernGraphicsCanvas canvas(renderer);
	REQUIRE(surface.str().empty());
}

TEST_CASE("CModernGraphicsCanvas: MoveTo draws nothing")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	CModernGraphicsCanvas canvas(renderer);

	canvas.MoveTo(FIRST.x, FIRST.y);
	REQUIRE(surface.str().empty());
}

TEST_CASE("CModernGraphicsCanvas: LineTo without preceding BeginDraw throws exception")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	CModernGraphicsCanvas canvas(renderer);

	REQUIRE_THROWS(canvas.LineTo(SECOND.x, SECOND.y));
}

TEST_CASE("CModernGraphicsCanvas: default pen position is (0, 0)")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	CModernGraphicsCanvas canvas(renderer);

	renderer.BeginDraw();
	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: MoveTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	CModernGraphicsCanvas canvas(renderer);

	renderer.BeginDraw();
	canvas.MoveTo(FIRST.x, FIRST.y);
	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: LineTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	CModernGraphicsCanvas canvas(renderer);

	renderer.BeginDraw();
	canvas.LineTo(FIRST.x, FIRST.y);
	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"-10\" toY=\"20\"/>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: destroying object after BeginDraw does not call EndDraw")
{
	std::ostringstream surface;
	CModernGraphicsRenderer renderer(surface);
	{
		CModernGraphicsCanvas canvas(renderer);
		renderer.BeginDraw();
	}
	REQUIRE(surface.str() == "<draw>\n");
}
