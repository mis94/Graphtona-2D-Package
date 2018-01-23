#include "..\..\Header Files\Color\BlackColorChanger.h"

void BlackColorChanger::colorize(HWND hWnd)
{
	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 0));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}