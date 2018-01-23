#include "..\..\Header Files\Clipping\RectangleClipper.h"

RectangleClipper::RectangleClipper()
{
	yTop = 60;
	yBottom = 500;
	xLeft = 60;
	xRight = 500;
	drawClippingShape();
}

RectangleClipper::RectangleClipper(int yTop, int yBottom, int xLeft, int xRight)
{
	RectangleClipper::yTop = yTop;
	RectangleClipper::yBottom = yBottom;
	RectangleClipper::xLeft = xLeft;
	RectangleClipper::xRight = xRight;
	drawClippingShape();
}

void RectangleClipper::drawClippingShape()
{
	LineDrawer *lineDrawer = new BresenhamLineDrawer();
	lineDrawer->drawLine(Point(xLeft, yTop), Point(xRight, yTop));
	lineDrawer->drawLine(Point(xLeft, yBottom), Point(xRight, yBottom));
	lineDrawer->drawLine(Point(xLeft, yTop), Point(xLeft, yBottom));
	lineDrawer->drawLine(Point(xRight, yTop), Point(xRight, yBottom));
}

void RectangleClipper::clipPoint(Point point)
{
	if (point.x <= xRight&&point.x >= xLeft)
	{
		if (point.y >= yTop&&point.y <= yBottom)
			SetPixel(hdc, point.x, point.y, RGB(0, 0, 0));
	}
}

void RectangleClipper::horizontalIntersect(Point startPoint, Point endPoint, int y, double *xi, double *yi)
{
	*yi = y;
	*xi = startPoint.x + (y - startPoint.y) * (endPoint.x - startPoint.x) / (endPoint.y - startPoint.y);
}

void RectangleClipper::verticalIntersect(Point startPoint, Point endPoint, int x, double *xi, double *yi)
{
	*xi = x;
	*yi = startPoint.y + (x - startPoint.x) * (endPoint.y - startPoint.y) / (endPoint.x - startPoint.x);
}

OutCode RectangleClipper::getOutCode(Point point)
{
	OutCode out;
	out.All = 0;

	if (point.x < xLeft)
		out.left = 1;
	if (point.x > xRight)
		out.right = 1;

	if (point.y < yTop)
		out.top = 1;
	if (point.y > yBottom)
		out.bottom = 1;

	return out;
}

void RectangleClipper::clipLine(Point startPoint, Point endPoint)
{
	//double x1 = startPoint.x, x2 = endPoint.x, y1 = startPoint.y, y2 = endPoint.y;
	OutCode out1 = getOutCode(startPoint);
	OutCode out2 = getOutCode(endPoint);
	// we stop the loop if all = 0 (draw) or both have a common side (clip)
	while ((out1.All || out2.All) && !(out1.All & out2.All))
	{
		double xi, yi;
		if (out1.All)
		{
			if (out1.left)
				verticalIntersect(startPoint, endPoint, xLeft, &xi, &yi);
			else if (out1.right)
				verticalIntersect(startPoint, endPoint, xRight, &xi, &yi);
			else if (out1.top)
				horizontalIntersect(startPoint, endPoint, yTop, &xi, &yi);
			else
				horizontalIntersect(startPoint, endPoint, yBottom, &xi, &yi);
			startPoint.x = xi;
			startPoint.y = yi;
			out1 = getOutCode(startPoint);
		}
		else
		{
			if (out2.left)
				verticalIntersect(startPoint, endPoint, xLeft, &xi, &yi);
			else if (out2.right)
				verticalIntersect(startPoint, endPoint, xRight, &xi, &yi);
			else if (out2.top)
				horizontalIntersect(startPoint, endPoint, yTop, &xi, &yi);
			else
				horizontalIntersect(startPoint, endPoint, yBottom, &xi, &yi);
			endPoint.x = xi;
			endPoint.y = yi;
			out2 = getOutCode(endPoint);
		}
	}
	LineDrawer *lineDrawer = new BresenhamLineDrawer();
	if (!out1.All && !out2.All)
		lineDrawer->drawLine(startPoint, endPoint);
}

