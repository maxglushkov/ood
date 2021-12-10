#include <catch2/catch.hpp>
#include <sstream>
#include "../modern-adapter.hpp"
using app::CModernGraphicsCanvas;

const static modern_graphics_lib::CPoint FIRST(-10, 20), SECOND(10, -20);

TEST_CASE("CModernGraphicsCanvas: creating object calls BeginDraw")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);
	REQUIRE(surface.str() == "<draw>\n");
}

TEST_CASE("CModernGraphicsCanvas: MoveTo draws nothing")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.MoveTo(FIRST.x, FIRST.y);
	REQUIRE(surface.str() == "<draw>\n");
}

TEST_CASE("CModernGraphicsCanvas: default pen position is (0, 0)")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: MoveTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.MoveTo(FIRST.x, FIRST.y);
	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: LineTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.LineTo(FIRST.x, FIRST.y);
	canvas.LineTo(SECOND.x, SECOND.y);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"-10\" toY=\"20\"/>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\"/>\n");
}

TEST_CASE("CModernGraphicsCanvas: destroying object calls EndDraw")
{
	std::ostringstream surface;
	{
		CModernGraphicsCanvas canvas(surface);
	}
	REQUIRE(surface.str() == "<draw>\n</draw>\n");
}
