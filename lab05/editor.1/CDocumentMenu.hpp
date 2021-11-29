#pragma once
#include "CMenu.hpp"
#include "IDocument.hpp"

class CDocumentMenu: public CMenu
{
public:
	CDocumentMenu(IDocument & document);
};
