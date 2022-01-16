#include "CanonicalShape.hpp"

void CanonicalShape::Draw(ICanvas & canvas)const
{
	DrawPath(canvas);
	canvas.SetColor(Color::YELLOW);
	canvas.FillPreserve();
	canvas.SetColor(Color::RED);
	canvas.Stroke();
}
