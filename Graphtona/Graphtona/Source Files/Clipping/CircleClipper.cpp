#include "..\..\Header Files\Clipping\CircleClipper.h"

CircleClipper::CircleClipper()
{
	center.x = 450;
	center.y = 250;
	radius = 150;
	drawClippingShape();
}

CircleClipper::CircleClipper(Point center, int radius)
{
	CircleClipper::center.x = center.x;
	CircleClipper::center.y = center.y;
	CircleClipper::radius = radius;
	drawClippingShape();
}

void CircleClipper::drawClippingShape()
{
	CircleDrawer *circleDrawer = new BresenhamCircleDrawer();
	circleDrawer->drawCircle(center, radius);
}

void CircleClipper::clipPoint(Point point)
{
	int distance = sqrt((point.x - center.x)*(point.x - center.x) + (point.y - center.y)*(point.y - center.y));
	if (distance <= radius)
		SetPixel(hdc, point.x, point.y, RGB(0, 0, 0));
}

void CircleClipper::clipLine(Point startPoint, Point endPoint)
{
	int dx = endPoint.x - startPoint.x, dy = endPoint.y - startPoint.y, steps, k;
	float xIncrement, yIncrement, x = startPoint.x, y = startPoint.y;
	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	xIncrement = dx / (float)steps;
	yIncrement = dy / (float)steps;

	double rClipping;

	for (int k = 0; k < steps; k++) {
		rClipping = sqrt((x - center.x)*(x - center.x) + (y - center.y)*(y - center.y));
		if (rClipping < radius) {
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
		x += xIncrement;
		y += yIncrement;
	}
}