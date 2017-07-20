#include "..\..\Header Files\Line\BresenhamLineDrawer.h"

void BresenhamLineDrawer::drawLine(HDC hdc, double xs, double ys, double xe, double ye)
{
	int ixs = (int)xs;
	int iys = (int)ys;
	int ixe = (int)xe;
	int iye = (int)ye;

	int deltaX = ixe - ixs;
	int deltaY = iye - iys;

	if (abs(deltaY) <= abs(deltaX))
	{
		if (ixs > ixe)
		{
			swap(ixs, ixe);
			swap(iys, iye);
			deltaX = abs(deltaX);
			deltaY = abs(deltaY);
		}

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
			deltaX = abs(deltaX);
			deltaY = abs(deltaY);
		}

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