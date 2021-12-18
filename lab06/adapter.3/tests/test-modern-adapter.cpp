#include <catch2/catch.hpp>
#include "../modern-adapter.hpp"
using app::CModernGraphicsCanvas;

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

	canvas.MoveTo(-10, 20);
	REQUIRE(surface.str() == "<draw>\n");
}

TEST_CASE("CModernGraphicsCanvas: SetColor draws nothing")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.SetColor(0xff3301);
	REQUIRE(surface.str() == "<draw>\n");
}

TEST_CASE("CModernGraphicsCanvas: default pen position is (0, 0), color is {r: 0, g: 0, b: 0, a: 1}")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.LineTo(10, -20);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"-20\">\n"
		"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n");
}

TEST_CASE("CModernGraphicsCanvas: MoveTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.MoveTo(-10, 20);
	canvas.LineTo(10, -20);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\">\n"
		"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n");
}

TEST_CASE("CModernGraphicsCanvas: LineTo changes pen position")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.LineTo(-10, 20);
	canvas.LineTo(10, -20);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"-10\" toY=\"20\">\n"
		"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n"
		"  <line fromX=\"-10\" fromY=\"20\" toX=\"10\" toY=\"-20\">\n"
		"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
		"  </line>\n");
}

TEST_CASE("CModernGraphicsCanvas: SetColor changes pen color")
{
	std::ostringstream surface;
	CModernGraphicsCanvas canvas(surface);

	canvas.SetColor(0xff3301);
	canvas.LineTo(10, -20);
	REQUIRE(surface.str() == "<draw>\n"
		"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"-20\">\n"
		"    <color r=\"1\" g=\"0.2\" b=\"0.00392157\" a=\"1\" />\n"
		"  </line>\n");
}

TEST_CASE("CModernGraphicsCanvas: destroying object calls EndDraw")
{
	std::ostringstream surface;
	{
		CModernGraphicsCanvas canvas(surface);
	}
	REQUIRE(surface.str() == "<draw>\n</draw>\n");
}
