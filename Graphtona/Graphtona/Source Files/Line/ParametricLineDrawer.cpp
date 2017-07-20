#include "..\..\Header Files\Line\ParametricLineDrawer.h"

void ParametricLineDrawer::drawLine(HDC hdc, Point startPoint, Point endPoint)
{
	int numberOfPoints = max(abs(startPoint.x - endPoint.x), abs(startPoint.y - endPoint.y));
	double dt = 1.0 / numberOfPoints;
	double x = startPoint.x, y = startPoint.y;
	double dx = dt*(endPoint.x - startPoint.x);
	double dy = dt*(endPoint.y - startPoint.y);
	for (double t = 1;t <= numberOfPoints;t++)
	{
		SetPixel(hdc, round(x), round(y), RGB(26, 29, 94));
		x += dx;
		y += dy;
	}
}