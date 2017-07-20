#pragma once
#include "..\Algorithm.h"

class EllipseDrawer : public Algorithm
{
public:
	void drawEllipse(HDC hdc, Point center, int width, int height);
};