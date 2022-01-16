#include "Ellipse.hpp"
#include "Rectangle.hpp"
#include "Triangle.hpp"

ICanvasPresenterItemPtr MakeCanvasPresenterItem(IDrawingItem const& drawingItem)
{
	ICanvasPresenterItemPtr presenterItem;
	const BoundingBox bounds = drawingItem.GetBoundingBox();
	switch (drawingItem.GetType())
	{
		case IDrawingItem::Type::Ellipse:
			presenterItem = std::make_unique<Ellipse>(bounds);
			break;
		case IDrawingItem::Type::Rectangle:
			presenterItem = std::make_unique<Rectangle>(bounds);
			break;
		case IDrawingItem::Type::Triangle:
			presenterItem = std::make_unique<Triangle>(bounds);
	}
	return presenterItem;
}
