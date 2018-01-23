#include "..\..\Header Files\Circle\BasicPolarCircleDrawer.h"

void BasicPolarCircleDrawer::drawCircle(Point center, int radius)
{
	double dtheta = 1.0 / radius;
	double x, y;
	for (double theta = 0;theta < PI / 4;theta += dtheta)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		draw8Points(center, round(x), round(y));
	}
}