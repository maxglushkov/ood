#pragma once
#include <variant>
#include "IImage.hpp"
#include "IParagraph.hpp"

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage()const
	{
		return Get<IImage>();
	}

	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph()const
	{
		return Get<IParagraph>();
	}

	virtual ~CConstDocumentItem() = default;

protected:
	typedef std::variant<IImagePtr, IParagraphPtr> Item;

	CConstDocumentItem(Item && item)
		:m_item(std::move(item))
	{}

	template<typename T>
	std::shared_ptr<const T> Get()const
	{
		const auto item = std::get_if<std::shared_ptr<T>>(&m_item);
		return item ? *item : nullptr;
	}

	template<typename T>
	std::shared_ptr<T> Get()
	{
		const auto item = std::get_if<std::shared_ptr<T>>(&m_item);
		return item ? *item : nullptr;
	}

private:
	Item m_item;
};
