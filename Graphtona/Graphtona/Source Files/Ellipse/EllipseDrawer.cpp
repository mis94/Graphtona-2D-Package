#include "..\..\Header Files\Ellipse\EllipseDrawer.h"

void EllipseDrawer::drawEllipse(HDC hdc, int xc, int yc, int width, int height)
{
	int a2 = width * width;
	int b2 = height * height;
	int fa2 = 4 * a2, fb2 = 4 * b2;
	int x, y, sigma;
	COLORREF color = RGB(255, 0, 0);

	for (x = 0, y = height, sigma = 2 * b2 + a2*(1 - 2 * height); b2*x <= a2*y; x++)
	{

		SetPixel(hdc, xc + x, yc + y, color);
		SetPixel(hdc, xc - x, yc + y, color);
		SetPixel(hdc, xc + x, yc - y, color);
		SetPixel(hdc, xc - x, yc - y, color);
		if (sigma >= 0)
		{
			sigma += fa2 * (1 - y);
			y--;
		}
		sigma += b2 * ((4 * x) + 6);
	}

	for (x = width, y = 0, sigma = 2 * a2 + b2*(1 - 2 * width); a2*y <= b2*x; y++)
	{
		SetPixel(hdc, xc + x, yc + y, color);
		SetPixel(hdc, xc - x, yc + y, color);
		SetPixel(hdc, xc + x, yc - y, color);
		SetPixel(hdc, xc - x, yc - y, color);
		if (sigma >= 0)
		{
			sigma += fb2 * (1 - x);
			x--;
		}
		sigma += a2 * ((4 * y) + 6);
	}
}
