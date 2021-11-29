#pragma once
#include <vector>
#include "CHistory.hpp"
#include "IDocument.hpp"

class CDocument: public IDocument
{
public:
	std::shared_ptr<IParagraph> InsertParagraph(std::string const& text, std::optional<size_t> position = std::nullopt)override;

	std::shared_ptr<IImage> InsertImage(std::filesystem::path const& path, int width, int height, std::optional<size_t> position = std::nullopt)override;

	size_t GetItemsCount()const override
	{
		return m_items.size();
	}

	CConstDocumentItem GetItem(size_t index)const override
	{
		return m_items[CheckIndex(index)];
	}

	CDocumentItem GetItem(size_t index)override
	{
		return m_items[CheckIndex(index)];
	}

	void DeleteItem(size_t index)override;

	std::string GetTitle()const override
	{
		return m_title;
	}

	void SetTitle(std::string const& title)override;

	bool CanUndo()const override
	{
		return m_history.CanUndo();
	}

	void Undo()override
	{
		m_history.Undo();
	}

	bool CanRedo()const override
	{
		return m_history.CanRedo();
	}

	void Redo()override
	{
		m_history.Redo();
	}

	void Save(std::filesystem::path const& path)const override;

private:
	std::string m_title;
	std::vector<CDocumentItem> m_items;
	CHistory m_history;

	template<typename T, typename ...Args>
	std::shared_ptr<T> Insert(std::optional<size_t> position, Args... args);

	size_t CheckIndex(size_t index)const
	{
		if (index >= GetItemsCount())
		{
			throw std::out_of_range("unexistant item");
		}
		return index;
	}

	size_t CheckPosition(std::optional<size_t> position)const
	{
		if (!position.has_value())
		{
			return GetItemsCount();
		}
		if (*position > GetItemsCount())
		{
			throw std::out_of_range("unexistant position");
		}
		return *position;
	}
};
