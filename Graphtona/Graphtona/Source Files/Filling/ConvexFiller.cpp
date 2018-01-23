#include "..\..\Header Files\Filling\ConvexFiller.h"

void ConvexFiller::convexFill(Point* points, int numberOfPoints)
{
	EdgeRecord *table = new EdgeRecord[800];
	Point v1 = points[numberOfPoints - 1];
	for (int i = 0;i < numberOfPoints;i++)
	{
		Point v2 = points[i];
		if (v1.y == v2.y)
			goto horizontal;
		if (v1.y > v2.y)
			swap(v1, v2);
		int y = v1.y;
		double x = v1.x;
		double mi = (v2.x - v1.x) / (double)(v2.y - v1.y);
		while (y < v2.y)
		{
			if (x < table[y].xLeft)
				table[y].xLeft = ceil(x);
			if (x > table[y].xRight)
				table[y].xRight = floor(x);
			x += mi;
			y++;
		}
	horizontal:v1 = points[i];
	}

	LineDrawer *lineDrawer = new BresenhamLineDrawer();
	for (int i = 0;i < 800;i++)
	{
		if (table[i].xLeft < table[i].xRight)
			lineDrawer->drawLine(Point(table[i].xLeft, i), Point(table[i].xRight, i));
	}
}

void ConvexFiller::fillCircle(Point center, int radius)
{
	CircleDrawer *circleDrawer = new BresenhamCircleDrawer();
	for (int i = radius;i >= 0;i--)
		circleDrawer->drawCircle(center, i);
}