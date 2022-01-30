#include "../history/IHistory.hpp"
#include "../history/SetCommand.hpp"
#include "IDrawingItemVisitor.hpp"
#include "RectangularShape.hpp"
#include "shapes.hpp"

template<typename T>
void RectangularShape<T>::BeginBoundingBoxOperation(IHistory & history)
{
	history.BeginOperation(std::make_unique<SetCommand<BoundingBox>>(m_bounds, m_bounds));
}

template<typename T>
void RectangularShape<T>::AcceptVisitor(IDrawingItemVisitor & visitor)const
{
	visitor.Visit(*this);
}

template class RectangularShape<Ellipse>;
template class RectangularShape<Rectangle>;
template class RectangularShape<Triangle>;
