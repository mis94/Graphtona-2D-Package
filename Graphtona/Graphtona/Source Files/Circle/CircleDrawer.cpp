#include "..\..\Header Files\Circle\CircleDrawer.h"

void CircleDrawer::draw8Points(Point center, int a, int b)
{
	SetPixel(hdc, center.x + a, center.y + b, RGB(0, 0, 0));
	SetPixel(hdc, center.x - a, center.y + b, RGB(0, 0, 0));
	SetPixel(hdc, center.x + a, center.y - b, RGB(0, 0, 0));
	SetPixel(hdc, center.x - a, center.y - b, RGB(0, 0, 0));
	SetPixel(hdc, center.x + b, center.y + a, RGB(0, 0, 0));
	SetPixel(hdc, center.x - b, center.y + a, RGB(0, 0, 0));
	SetPixel(hdc, center.x + b, center.y - a, RGB(0, 0, 0));
	SetPixel(hdc, center.x - b, center.y - a, RGB(0, 0, 0));
}