#include "..\..\Header Files\Line\ParametricLineDrawer.h"

void ParametricLineDrawer::drawLine(HDC hdc, double xs, double ys, double xe, double ye)
{
	int numberOfPoints = max(abs(xs - xe), abs(ys - ye));
	double dt = 1.0 / numberOfPoints;
	double x = xs, y = ys;
	double dx = dt*(xe - xs);
	double dy = dt*(ye - ys);
	for (double t = 1;t <= numberOfPoints;t++)
	{
		SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		x += dx;
		y += dy;
	}
}