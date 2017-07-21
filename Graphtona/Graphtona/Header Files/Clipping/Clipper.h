#pragma once
#include "..\Algorithm.h"

class Clipper : public Algorithm
{
public:
	virtual void drawClippingShape(HDC hdc) = 0;
};
