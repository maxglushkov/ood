#include <iostream>
#include "CDocument.hpp"
#include "CDocumentMenu.hpp"

int main()
{
	CDocument document;
	CDocumentMenu(document).Run(std::cin, std::cout, std::cerr);
	return 0;
}
