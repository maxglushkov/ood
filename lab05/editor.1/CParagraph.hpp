#pragma once
#include "CHistory.hpp"
#include "IParagraph.hpp"

class CParagraph: public IParagraph
{
public:
	CParagraph(CHistory & history, std::string const& text)
		:m_history(history)
		,m_text(text)
	{}

	std::string GetText()const override
	{
		return m_text;
	}

	void SetText(std::string const& text)override;

private:
	CHistory & m_history;
	std::string m_text;
};
