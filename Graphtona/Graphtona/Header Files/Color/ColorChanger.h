#pragma once
#include "..\Algorithm.h"

class ColorChanger : public Algorithm
{
public:
	virtual void colorize(HWND hWnd) = 0;
};