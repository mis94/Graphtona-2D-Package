#include "BresenhamCircleDrawer.h"

void BresenhamCircleDrawer::drawCircle(HDC hdc, double xc, double yc, int radius)
{
	int x = 0;
	int y = radius;

	draw8Points(hdc, xc, yc, x, y);

	int d = 1 - radius;
	int d1 = 3;
	int d2 = 5 - (2 * radius);

	while (x < y)
	{
		if (d < 0)
		{
			d += d1;
			d2 += 2;
		}
		else
		{
			d += d2;
			d2 += 4;
			y--;
		}
		x++;
		d1 += 2;
		draw8Points(hdc, xc, yc, x, y);
	}
}