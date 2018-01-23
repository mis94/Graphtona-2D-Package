#pragma once
#include "Clipper.h"
#include "..\Circle\BresenhamCircleDrawer.h"

class CircleClipper : public Clipper
{
private:
	Point center;
	int radius;
public:
	CircleClipper();
	CircleClipper(Point center, int radius);
	void drawClippingShape();
	void clipPoint(Point point);
	void clipLine(Point startPoint, Point endPoint);
};