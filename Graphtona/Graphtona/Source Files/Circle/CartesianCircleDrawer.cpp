#include "..\..\Header Files\Circle\CartesianCircleDrawer.h"

void CartesianCircleDrawer::drawCircle(HDC hdc, double xc, double yc, int radius)
{
	double x = 0;
	double y = radius;

	while (x < y)
	{
		draw8Points(hdc, xc, yc, round(x), round(y));
		x = x + 1;
		y = sqrt(radius*radius - x*x);
	}
}