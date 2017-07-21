#pragma once
#include "Clipper.h"
#include "..\Circle\BresenhamCircleDrawer.h"

class CircleClipper : public Clipper
{
private:
	Point center;
	int radius;
public:
	CircleClipper(HDC hdc);
	CircleClipper(HDC hdc, Point center, int radius);
	void drawClippingShape(HDC hdc);
	void clipPoint(HDC hdc, Point point);
	void clipLine(HDC hdc, Point startPoint, Point endPoint);
};