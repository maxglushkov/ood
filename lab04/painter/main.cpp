#include <CDesigner.hpp>
#include <CShapeFactory.hpp>
#include <iostream>
#include "CClient.hpp"
#include "CSvgCanvas.hpp"

int main()
{
	CShapeFactory factory;
	CDesigner designer(factory);
	const auto draft = CClient::VisitDesigner(designer, std::cin);

	CSvgCanvas canvas(std::cout);
	CClient::VisitPainter(draft, canvas);
	return 0;
}
