#pragma once
#include "..\Algorithm.h"

class CurveDrawer : public Algorithm
{
public:
	virtual void drawCurve(Point startPoint, Point endPoint, Point slopes[]) = 0;
	int mulitplyTwoVectors(int v1[], int v2[], int size);
};
