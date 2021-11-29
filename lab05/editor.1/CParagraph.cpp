#include "CParagraph.hpp"
#include "CSetCommand.hpp"

void CParagraph::SetText(std::string const& text)
{
	m_history.Do(std::make_unique<CSetCommand<std::string>>(m_text, text));
}
