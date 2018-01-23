#include "..\..\Header Files\Circle\CartesianCircleDrawer.h"

void CartesianCircleDrawer::drawCircle(Point center, int radius)
{
	double x = 0;
	double y = radius;

	while (x < y)
	{
		draw8Points(center, round(x), round(y));
		x = x + 1;
		y = sqrt(radius*radius - x*x);
	}
}