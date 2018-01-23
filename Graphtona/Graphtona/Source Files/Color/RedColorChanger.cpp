#include "..\..\Header Files\Color\RedColorChanger.h"

void RedColorChanger::colorize(HWND hWnd)
{
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 0, 0));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}