#pragma once
#include "Clipper.h"
#include "..\Line\ParametricLineDrawer.h"

union OutCode
{
	unsigned All : 4;
	struct {
		unsigned left : 1, top : 1, right : 1, bottom : 1;
	};
};

class RectangleClipper : public Clipper
{
private:
	int yTop;
	int yBottom;
	int xLeft;
	int xRight;
	void horizontalIntersect(Point startPoint, Point endPoint, int y, double *xi, double *yi);
	void verticalIntersect(Point startPoint, Point endPoint, int x, double *xi, double *yi);
	OutCode getOutCode(Point point);
public:
	RectangleClipper(HDC hdc);
	RectangleClipper(HDC hdc, int yTop, int yBottom, int xLeft, int xRight);
	void drawClippingShape(HDC hdc);
	void clipPoint(HDC hdc, Point point);
	void clipLine(HDC hdc, Point startPoint, Point endPoint);
};