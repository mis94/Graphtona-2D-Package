#include "..\..\Header Files\Line\DDALineDrawer.h"

void DDALineDrawer::drawLine(HDC hdc, Point startPoint, Point endPoint)
{
	double dx = endPoint.x - startPoint.x;
	double dy = endPoint.y - startPoint.y;

	if (abs(dy) < abs(dx)) // slope < 1, x is the independent variable
	{
		double slope = dy / dx;

		if (startPoint.x > endPoint.x)
		{
			swap(startPoint.x, endPoint.x);
			swap(startPoint.y, endPoint.y);
		}

		int x = startPoint.x;
		double y = startPoint.y;
		SetPixel(hdc, x, y, RGB(max(x + y, 255), x, y));

		while (x < endPoint.x)
		{
			x++;
			y += slope;
			SetPixel(hdc, x, y, RGB(x, max(x + y, 255), y));
		}
	}
	else // slope > 1, y is the independent variable
	{
		double slope = dx / dy;

		if (startPoint.y > endPoint.y)
		{
			swap(startPoint.x, endPoint.x);
			swap(startPoint.y, endPoint.y);
		}

		double x = startPoint.x;
		int y = startPoint.y;
		SetPixel(hdc, x, y, RGB(y, x, max(x + y, 255)));

		while (y < endPoint.y)
		{
			y++;
			x += slope;
			SetPixel(hdc, x, y, RGB(y, max(x + y, 255), x));
		}
	}
}