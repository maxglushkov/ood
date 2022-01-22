#pragma once
#include <memory>
#include "../drawing/IDrawingItem.hpp"
#include "ICanvas.hpp"

struct ICanvasPresenterItem
{
	virtual ~ICanvasPresenterItem() = default;

	virtual bool HitTest(Point const& point)const = 0;

	virtual void Draw(ICanvas & canvas)const = 0;
};

typedef std::unique_ptr<ICanvasPresenterItem> ICanvasPresenterItemPtr;

ICanvasPresenterItemPtr MakeCanvasPresenterItem(IDrawingItem const& drawingItem);
