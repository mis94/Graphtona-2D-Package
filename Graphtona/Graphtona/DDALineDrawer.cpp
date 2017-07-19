#include "DDALineDrawer.h"

void DDALineDrawer::drawLine(HDC hdc, double xs, double ys, double xe, double ye)
{
	double dx = xe - xs;
	double dy = ye - ys;

	if (abs(dy) < abs(dx)) // slope < 1, x is the independent variable
	{
		double slope = dy / dx;

		if (xs > xe)
		{
			swap(xs, xe);
			swap(ys, ye);
		}

		int x = xs;
		double y = ys;
		SetPixel(hdc, x, y, RGB(max(x + y, 255), x, y));

		while (x < xe)
		{
			x++;
			y += slope;
			SetPixel(hdc, x, y, RGB(x, max(x + y, 255), y));
		}
	}
	else // slope > 1, y is the independent variable
	{
		double slope = dx / dy;

		if (ys > ye)
		{
			swap(xs, xe);
			swap(ys, ye);
		}

		double x = xs;
		int y = ys;
		SetPixel(hdc, x, y, RGB(y, x, max(x + y, 255)));

		while (y < ye)
		{
			y++;
			x += slope;
			SetPixel(hdc, x, y, RGB(y, max(x + y, 255), x));
		}
	}
}