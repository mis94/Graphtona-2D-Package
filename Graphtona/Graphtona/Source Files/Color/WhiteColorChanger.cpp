#include "..\..\Header Files\Color\WhiteColorChanger.h"

void WhiteColorChanger::colorize(HWND hWnd)
{
	HBRUSH hbrush = CreateSolidBrush(RGB(255, 255, 255));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}