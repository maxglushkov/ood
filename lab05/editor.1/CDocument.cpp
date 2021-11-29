#include <fstream>
#include "CDocument.hpp"
#include "CImage.hpp"
#include "CParagraph.hpp"
#include "CSetCommand.hpp"
#include "CVectorCommand.hpp"

std::string HtmlEscape(std::string const& text);

std::shared_ptr<IParagraph> CDocument::InsertParagraph(std::string const& text, std::optional<size_t> position)
{
	return Insert<CParagraph>(position, text);
}

std::shared_ptr<IImage> CDocument::InsertImage(std::filesystem::path const& path, int width, int height, std::optional<size_t> position)
{
	return Insert<CImage>(position, path, width, height);
}

void CDocument::DeleteItem(size_t index)
{
	m_history.Do(std::make_unique<CVectorCommand<CDocumentItem>>(m_items, CheckIndex(index), std::nullopt));
}

void CDocument::SetTitle(std::string const& title)
{
	m_history.Do(std::make_unique<CSetCommand<std::string>>(m_title, title));
}

void CDocument::Save(std::filesystem::path const& path)const
{
	std::ofstream file(path);
	file << "<!DOCTYPE html>\n"
	     << "<html>\n"
	     << "\t<head>\n"
	     << "\t\t<title>" << HtmlEscape(m_title) << "</title>\n"
	     << "\t</head>\n"
	     << "\t<body>\n";
	for (auto & item: m_items)
	{
		if (auto paragraph = item.GetParagraph())
		{
			file << "\t\t<p>" << HtmlEscape(paragraph->GetText()) << "</p>\n";
		}
		else if (auto image = item.GetImage())
		{
			file << "\t\t<img src=\"" << HtmlEscape(image->GetPath())
			           << "\" width=\"" << image->GetWidth()
			           << "\" height=\"" << image->GetHeight() << "\">\n";
		}
	}
	file << "\t</body>\n"
	     << "</html>";
}

template<typename T, typename ...Args>
std::shared_ptr<T> CDocument::Insert(std::optional<size_t> position, Args... args)
{
	const size_t checkedPos = CheckPosition(position);
	const auto item = std::make_shared<T>(m_history, args...);
	m_history.Do(std::make_unique<CVectorCommand<CDocumentItem>>(m_items, checkedPos, CDocumentItem(item)));
	return item;
}

std::string HtmlEscape(std::string const& text)
{
	std::string html;
	for (char c: text)
	{
		switch (c)
		{
			case '"':
				html.append("&quot;");
				break;
			case '&':
				html.append("&amp;");
				break;
			case '\'':
				html.append("&apos;");
				break;
			case '>':
				html.append("&gt;");
				break;
			case '<':
				html.append("&lt;");
				break;
			default:
				html.push_back(c);
		}
	}
	return html;
}
