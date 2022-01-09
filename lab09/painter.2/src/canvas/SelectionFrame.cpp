#include "SelectionFrame.hpp"

constexpr static RGBAColor OUTLINE_COLOR(0.0, 0.0, 0.0);
constexpr static double OUTLINE_DASH_LENGTH = 5.0;
constexpr static double OUTLINE_WIDTH = 1.0;

constexpr static double MARKER_RADIUS = 4.0;
constexpr static RGBAColor MARKER_COLOR(0.0, 0.75, 0.0);

constexpr static double FRAME_WIDTH = 2.0 * MARKER_RADIUS;

static void DrawMarker(ICanvas & canvas, double cx, double cy)
{
	canvas.DrawEllipse(cx, cy, MARKER_RADIUS, MARKER_RADIUS);
	canvas.SetColor(MARKER_COLOR);
	canvas.Fill();
}

Direction SelectionFrame::HitTest(Point const& point)const
{
	Direction hitBounds;
	if (m_item)
	{
		const BoundingBox bounds = m_item->GetBoundingBox();
		if (point.x >= bounds.xMin - FRAME_WIDTH
		 && point.y >= bounds.yMin - FRAME_WIDTH
		 && point.x <= bounds.xMax + FRAME_WIDTH
		 && point.y <= bounds.yMax + FRAME_WIDTH)
		{
			hitBounds.set(Direction::Left, point.x < bounds.xMin);
			hitBounds.set(Direction::Top, point.y < bounds.yMin);
			hitBounds.set(Direction::Right, point.x > bounds.xMax);
			hitBounds.set(Direction::Bottom, point.y > bounds.yMax);
		}
	}
	return hitBounds;
}

void SelectionFrame::Draw(ICanvas & canvas)const
{
	if (!m_item)
	{
		return;
	}
	BoundingBox bounds = m_item->GetBoundingBox();
	bounds.xMin -= MARKER_RADIUS;
	bounds.yMin -= MARKER_RADIUS;
	bounds.xMax += MARKER_RADIUS;
	bounds.yMax += MARKER_RADIUS;

	canvas.DrawRectangle(bounds);
	canvas.SetColor(OUTLINE_COLOR);
	canvas.SetDash(OUTLINE_DASH_LENGTH, OUTLINE_DASH_LENGTH);
	canvas.SetLineWidth(OUTLINE_WIDTH);
	canvas.Stroke();

	const double cx = (bounds.xMin + bounds.xMax) / 2.0;
	const double cy = (bounds.yMin + bounds.yMax) / 2.0;
	DrawMarker(canvas, bounds.xMin, bounds.yMin);
	DrawMarker(canvas, cx, bounds.yMin);
	DrawMarker(canvas, bounds.xMax, bounds.yMin);
	DrawMarker(canvas, bounds.xMax, cy);
	DrawMarker(canvas, bounds.xMax, bounds.yMax);
	DrawMarker(canvas, cx, bounds.yMax);
	DrawMarker(canvas, bounds.xMin, bounds.yMax);
	DrawMarker(canvas, bounds.xMin, cy);
}
