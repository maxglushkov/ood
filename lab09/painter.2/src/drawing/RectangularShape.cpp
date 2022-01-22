#include "../history/IHistory.hpp"
#include "../history/SetCommand.hpp"
#include "RectangularShape.hpp"

void RectangularShape::SetBoundingBox(IHistory * history, BoundingBox const& bounds)
{
	history->Do(std::make_unique<SetCommand<BoundingBox>>(m_bounds, bounds));
}
