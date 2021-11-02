#pragma once
#include <CPainter.hpp>
#include <IDesigner.hpp>

class CClient
{
public:
	static CPictureDraft VisitDesigner(IDesigner & designer, std::istream & wish)
	{
		return designer.CreateDraft(wish);
	}

	static void VisitPainter(CPictureDraft const& draft, ICanvas & canvas)
	{
		CPainter::DrawPicture(draft, canvas);
	}
};
