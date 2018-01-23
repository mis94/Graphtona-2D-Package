#pragma once
#include "Clipper.h"
#include "..\Line\BresenhamLineDrawer.h"

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
	RectangleClipper();
	RectangleClipper(int yTop, int yBottom, int xLeft, int xRight);
	void drawClippingShape();
	void clipPoint(Point point);
	void clipLine(Point startPoint, Point endPoint);
};