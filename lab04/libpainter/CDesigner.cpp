#include "CDesigner.hpp"

CPictureDraft CDesigner::CreateDraft(std::istream & input)
{
	CPictureDraft draft;
	std::string line;
	while (std::getline(input, line))
	{
		draft.AddShape(m_factory.CreateShape(line));
	}
	return draft;
}
