#include "ImprovedPolarCircleDrawer.h"

void ImprovedPolarCircleDrawer::drawCircle(HDC hdc, double xc, double yc, int radius)
{
	double dtheta = 1.0 / radius;
	double ct = cos(dtheta);
	double st = sin(dtheta);

	double x = radius;
	double y = 0;

	draw8Points(hdc, xc, yc, round(x), round(y));

	while (y < x)
	{
		double x1 = x*ct - y*st;
		y = x*st + y*ct;
		x = x1;
		draw8Points(hdc, xc, yc, round(x), round(y));
	}
}