#include "../history/IHistory.hpp"
#include "../history/SetCommand.hpp"
#include "IDrawingItemVisitor.hpp"
#include "RectangularShape.hpp"

void RectangularShape::SetBoundingBox(IHistory * history, BoundingBox const& bounds)
{
	history->Do(std::make_unique<SetCommand<BoundingBox>>(m_bounds, bounds));
}

void RectangularShape::AcceptVisitor(IDrawingItemVisitor & visitor, Acceptor const& acceptor)const
{
	BoundingBox const& bounds = *(acceptor.m_bounds ?: &m_bounds);
	switch (m_type)
	{
		case Type::Ellipse:
			double rx, ry;
			rx = (bounds.xMax - bounds.xMin) / 2.0;
			ry = (bounds.yMax - bounds.yMin) / 2.0;
			visitor.VisitEllipse(bounds.xMin + rx, bounds.yMin + ry, rx, ry);
			break;
		case Type::Rectangle:
			visitor.VisitRectangle(bounds);
			break;
		case Type::Triangle:
			visitor.VisitTriangle(
				(bounds.xMax + bounds.xMin) / 2.0,
				bounds.yMin,
				bounds.xMin,
				bounds.xMax,
				bounds.yMax
			);
	}
}
