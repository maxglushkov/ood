#include "CanonicalShape.hpp"

constexpr static RGBAColor FILL_COLOR(1.0, 1.0, 0.0);
constexpr static RGBAColor OUTLINE_COLOR(1.0, 0.0, 0.0);
constexpr static double MIN_DIMENSION = 1.0;

static void FixDimension(double & min, double & max, bool preserveMin = true)
{
	if (max - min < MIN_DIMENSION)
	{
		if (preserveMin)
		{
			max = min + MIN_DIMENSION;
		}
		else
		{
			min = max - MIN_DIMENSION;
		}
	}
}

void CanonicalShape::Draw(ICanvas & canvas)const
{
	DrawPath(canvas);
	canvas.SetColor(FILL_COLOR);
	canvas.FillPreserve();
	canvas.SetColor(OUTLINE_COLOR);
	canvas.Stroke();
}

void CanonicalShape::MoveBoundsRelative(BoundingBox const& delta)
{
	m_bounds.xMin += delta.xMin;
	m_bounds.yMin += delta.yMin;
	m_bounds.xMax += delta.xMax;
	m_bounds.yMax += delta.yMax;
	FixDimension(m_bounds.xMin, m_bounds.xMax, !bool(delta.xMin));
	FixDimension(m_bounds.yMin, m_bounds.yMax, !bool(delta.yMin));
}
