#include "..\..\Header Files\Color\GrayColorChanger.h"

void GrayColorChanger::colorize(HWND hWnd)
{
	HBRUSH hbrush = CreateSolidBrush(RGB(128, 128, 128));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}