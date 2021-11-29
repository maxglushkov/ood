#pragma once
#include <catch2/catch.hpp>
#include "../IDocument.hpp"
#include "null-items.hpp"

struct InsertParagraph
{
	std::string text;
	std::optional<size_t> position;
	bool operator ==(InsertParagraph const&)const = default;
};

struct InsertImage
{
	std::filesystem::path path;
	int width, height;
	std::optional<size_t> position;
	bool operator ==(InsertImage const&)const = default;
};

struct GetItem
{
	size_t index;
	bool operator ==(GetItem const&)const = default;
};

struct DeleteItem
{
	size_t index;
	bool operator ==(DeleteItem const&)const = default;
};

struct SetTitle
{
	std::string title;
	bool operator ==(SetTitle const&)const = default;
};

struct Undo
{
	bool operator ==(Undo const&)const = default;
};

struct Redo
{
	bool operator ==(Redo const&)const = default;
};

class CLoggingDocument: public IDocument
{
public:
	typedef std::variant<::InsertParagraph, ::InsertImage, ::GetItem, ::DeleteItem, ::SetTitle, ::Undo, ::Redo> Command;

	CLoggingDocument(CDocumentItem && item = {std::make_shared<NullParagraph>()})
		:m_item(std::move(item))
	{}

	std::shared_ptr<IParagraph> InsertParagraph(std::string const& text, std::optional<size_t> position = std::nullopt)override
	{
		m_log.push_back(::InsertParagraph{text, position});
		return {};
	}

	std::shared_ptr<IImage> InsertImage(std::filesystem::path const& path, int width, int height, std::optional<size_t> position = std::nullopt)override
	{
		m_log.push_back(::InsertImage{path, width, height, position});
		return {};
	}

	size_t GetItemsCount()const override
	{
		return {};
	}

	CConstDocumentItem GetItem(size_t)const override
	{
		return m_item;
	}

	CDocumentItem GetItem(size_t index)override
	{
		m_log.push_back(::GetItem{index});
		return m_item;
	}

	void DeleteItem(size_t index)override
	{
		m_log.push_back(::DeleteItem{index});
	}

	std::string GetTitle()const override
	{
		return {};
	}

	void SetTitle(std::string const& title)override
	{
		m_log.push_back(::SetTitle{title});
	}

	bool CanUndo()const override
	{
		return {};
	}

	void Undo()override
	{
		m_log.push_back(::Undo{});
	}

	bool CanRedo()const override
	{
		return {};
	}

	void Redo()override
	{
		m_log.push_back(::Redo{});
	}

	void Save(std::filesystem::path const& path)const override
	{
		m_path = path;
	}

	void Match(std::initializer_list<Command> && commands)
	{
		REQUIRE(std::equal(m_log.begin(), m_log.end(), commands.begin(), commands.end()));
	}

	std::filesystem::path const& GetPath()
	{
		return m_path;
	}

private:
	std::vector<Command> m_log;
	CDocumentItem m_item;
	mutable std::filesystem::path m_path;
};
