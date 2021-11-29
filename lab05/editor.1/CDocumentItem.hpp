#pragma once
#include "CConstDocumentItem.hpp"

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(Item && item)
		:CConstDocumentItem(std::move(item))
	{}

	using CConstDocumentItem::GetImage;
	using CConstDocumentItem::GetParagraph;

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage()
	{
		return Get<IImage>();
	}

	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return Get<IParagraph>();
	}
};
