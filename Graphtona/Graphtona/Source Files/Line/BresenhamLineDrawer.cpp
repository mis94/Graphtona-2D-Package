#include "..\..\Header Files\Line\BresenhamLineDrawer.h"

void BresenhamLineDrawer::drawLine(Point startPoint, Point endPoint)
{
	int ixs = (int)startPoint.x; // converting all double variables to ints, as this algorithm works all integers
	int iys = (int)startPoint.y;
	int ixe = (int)endPoint.x;
	int iye = (int)endPoint.y;

	int deltaX = ixe - ixs;
	int deltaY = iye - iys;

	if (abs(deltaY) <= abs(deltaX))
	{
		if (ixs > ixe)
		{
			swap(ixs, ixe);
			swap(iys, iye);
		}

		deltaX = abs(deltaX);
		deltaY = abs(deltaY);
		int error = 2 * deltaY - deltaX;
		int d1 = 2 * deltaY;
		int d2 = 2 * (deltaY - deltaX);

		int x = ixs;
		int y = iys;

		int increment;
		if (iys < iye)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (x < ixe)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				y += increment;
			}
			x++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
	else
	{
		if (iys > iye)
		{
			swap(ixs, ixe);
			swap(iys, iye);
		}

		deltaX = abs(deltaX);
		deltaY = abs(deltaY);

		int error = 2 * deltaX - deltaY;
		int d1 = 2 * deltaX;
		int d2 = 2 * (deltaX - deltaY);

		int x = ixs;
		int y = iys;

		int increment;
		if (ixs < ixe)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (y < iye)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				x += increment;
			}
			y++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
}