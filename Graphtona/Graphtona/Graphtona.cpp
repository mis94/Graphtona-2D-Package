#include "Header Files\Line\DDALineDrawer.h"
#include "Header Files\Line\ParametricLineDrawer.h"
#include "Header Files\Line\BresenhamLineDrawer.h"
#include "Header Files\Circle\CartesianCircleDrawer.h"
#include "Header Files\Circle\BasicPolarCircleDrawer.h"
#include "Header Files\Circle\ImprovedPolarCircleDrawer.h"
#include "Header Files\Circle\BresenhamCircleDrawer.h"
#include "Header Files\Ellipse\EllipseDrawer.h"
#include "Header Files\Curve\FirstDegreeCurveDrawer.h"
#include "Header Files\Curve\SecondDegreeCurveDrawer.h"
#include "Header Files\Curve\HermiteCurveDrawer.h"
#include "Header Files\Curve\BezierCurveDrawer.h"
#include "Header Files\Filling\ConvexFiller.h"
#include "Header Files\Clipping\RectangleClipper.h"
#include "Header Files\Clipping\CircleClipper.h"

enum Color {
	Black,
	Red,
	White,
	Gray
};

void changeBackgroundColor(HWND hWnd, Color newColor)
{
	HBRUSH hbrush;
	if (newColor == Black)
		hbrush = CreateSolidBrush(RGB(0, 0, 0));
	else if (newColor == Red)
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
	else if (newColor == White)
		hbrush = CreateSolidBrush(RGB(255, 255, 255));
	else
		hbrush = CreateSolidBrush(RGB(128, 128, 128));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}

int algo1 = 1, algo2 = 2, algo3 = 3, algo4 = 4, algo5 = 5, algo6 = 6, algo7 = 7, algo8 = 8, algo9 = 9, algo10 = 10, ch = -1;
int algo11 = 11, algo12 = 12, algo13 = 13, algo14 = 14, algo15 = 15, algo16 = 16, algo17 = 17, algo18 = 18, algo19 = 19;
int algo20 = 20, algo21 = 21, algo22 = 22, algo23 = 23;

LPARAM WINAPI MyWindowProcedure(HWND hWnd, UINT mcode, WPARAM wp, LPARAM lp)
{
	HDC hdc; //handle of device context
	static double x1, y1, s1x, s1y, x2, y2, s2x, s2y;
	static bool isFirstPress = 1, isSecondPress = 1, isThirdPress = 1; // those could also be global

	switch (mcode) {
	case WM_CREATE: {
		HMENU hMenubar = CreateMenu();

		HMENU hFile1 = CreateMenu(); // background color
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile1, L"Change Background color");
		AppendMenu(hFile1, MF_STRING, algo1, L"Black");
		AppendMenu(hFile1, MF_STRING, algo2, L"Red");
		AppendMenu(hFile1, MF_STRING, algo3, L"White");
		AppendMenu(hFile1, MF_STRING, algo4, L"Gray");

		HMENU hFile2 = CreateMenu(); // line
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile2, L"Line");
		AppendMenu(hFile2, MF_STRING, algo5, L"Simple Line DDA");
		AppendMenu(hFile2, MF_STRING, algo6, L"Parametric line");
		AppendMenu(hFile2, MF_STRING, algo7, L"Bresenham midpoint algorithm");

		HMENU hFile3 = CreateMenu(); // circle
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile3, L"Circle");
		AppendMenu(hFile3, MF_STRING, algo8, L"Direct Cartesian method");
		AppendMenu(hFile3, MF_STRING, algo9, L"Polar direct method");
		AppendMenu(hFile3, MF_STRING, algo10, L"Iterative polar algorithm");
		AppendMenu(hFile3, MF_STRING, algo11, L"Bresenham midpoint algorithm");

		HMENU hFile7 = CreateMenu(); // ellipse
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile7, L"Ellipse");
		AppendMenu(hFile7, MF_STRING, algo23, L"Ellipse Drawing");

		HMENU hFile4 = CreateMenu(); // curve
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile4, L"Curve");
		AppendMenu(hFile4, MF_STRING, algo12, L"First Degree");
		AppendMenu(hFile4, MF_STRING, algo13, L"Second Degree");
		AppendMenu(hFile4, MF_STRING, algo14, L"Hermite");
		AppendMenu(hFile4, MF_STRING, algo15, L"Bezier");
		AppendMenu(hFile4, MF_STRING, algo16, L"Splines");

		HMENU hFile5 = CreateMenu(); // convex filling
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile5, L"Filling");
		AppendMenu(hFile5, MF_STRING, algo17, L"Convex filling");
		AppendMenu(hFile5, MF_STRING, algo22, L"Circle filling");

		HMENU hFile6 = CreateMenu(); // convex filling
		AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile6, L"Clipping");
		AppendMenu(hFile6, MF_STRING, algo18, L"Point according to rectangle");
		AppendMenu(hFile6, MF_STRING, algo19, L"Line according to rectangle");
		AppendMenu(hFile6, MF_STRING, algo20, L"Point according to circle");
		AppendMenu(hFile6, MF_STRING, algo21, L"Line according to circle");

		SetMenu(hWnd, hMenubar);
	}break;
	case WM_COMMAND:
	{
		if (LOWORD(wp) == algo1)
			changeBackgroundColor(hWnd, Black);
		else if (LOWORD(wp) == algo2)
			changeBackgroundColor(hWnd, Red);
		else if (LOWORD(wp) == algo3)
			changeBackgroundColor(hWnd, White);
		else if (LOWORD(wp) == algo4)
			changeBackgroundColor(hWnd, Gray);
		else if (LOWORD(wp) == algo5)
			ch = 5;
		else if (LOWORD(wp) == algo6)
			ch = 6;
		else if (LOWORD(wp) == algo7)
			ch = 7;
		else if (LOWORD(wp) == algo8)
			ch = 8;
		else if (LOWORD(wp) == algo9)
			ch = 9;
		else if (LOWORD(wp) == algo10)
			ch = 10;
		else if (LOWORD(wp) == algo11)
			ch = 11;
		else if (LOWORD(wp) == algo12)
			ch = 12;
		else if (LOWORD(wp) == algo13)
			ch = 13;
		else if (LOWORD(wp) == algo14)
			ch = 14;
		else if (LOWORD(wp) == algo15)
			ch = 15;
		else if (LOWORD(wp) == algo16)
			ch = 16;
		else if (LOWORD(wp) == algo17)
			ch = 17;
		else if (LOWORD(wp) == algo18)
			ch = 18;
		else if (LOWORD(wp) == algo19)
			ch = 19;
		else if (LOWORD(wp) == algo20)
			ch = 20;
		else if (LOWORD(wp) == algo21)
			ch = 21;
		else if (LOWORD(wp) == algo22)
			ch = 22;
		else if (LOWORD(wp) == algo23)
			ch = 23;

		isFirstPress = 1;
		isSecondPress = 1;
		isThirdPress = 1;
	}break;
	case WM_LBUTTONDOWN: {
		if (isFirstPress)
		{
			hdc = GetDC(hWnd);

			x1 = LOWORD(lp);
			y1 = HIWORD(lp);

			if (ch == 18)
			{
				RectangleClipper rectangleClipper(hdc);
				rectangleClipper.clipPoint(hdc, Point(x1, y1));
			}
			else if (ch == 20)
			{
				CircleClipper circleClipper(hdc);
				circleClipper.clipPoint(hdc, Point(x1, y1));
			}
			else
			{
				isFirstPress = 0;
				goto continueTakingInput1;
			}

			ReleaseDC(hWnd, hdc);
			isFirstPress = 1;continueTakingInput1:;
		}
		else if (isSecondPress)
		{
			hdc = GetDC(hWnd);

			x2 = LOWORD(lp);
			y2 = HIWORD(lp);

			if (ch == 5)
			{
				LineDrawer *lineDrawer = new DDALineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == 6)
			{
				LineDrawer *lineDrawer = new ParametricLineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == 7)
			{
				LineDrawer *lineDrawer = new BresenhamLineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == 8)
			{
				CircleDrawer *circleDrawer = new CartesianCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 9)
			{
				CircleDrawer *circleDrawer = new BasicPolarCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 10)
			{
				CircleDrawer *circleDrawer = new ImprovedPolarCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 11)
			{
				CircleDrawer *circleDrawer = new BresenhamCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 12)
			{
				CurveDrawer *curveDrawer = new FirstDegreeCurveDrawer();
				Point startPoint, endPoint;
				startPoint.x = x1;
				startPoint.y = y1;
				endPoint.x = x2;
				endPoint.y = y2;
				curveDrawer->drawCurve(hdc, startPoint, endPoint, {});
			}
			else if (ch == 22)
			{
				ConvexFiller convexFiller;
				convexFiller.fillCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 23)
			{
				EllipseDrawer ellipseDrawer;
				ellipseDrawer.drawEllipse(hdc, Point(x1, y1), 2 * sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == 19)
			{
				RectangleClipper rectangleClipper(hdc);
				rectangleClipper.clipLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == 21)
			{
				CircleClipper circleClipper(hdc);
				circleClipper.clipLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else
			{
				isSecondPress = 0;
				goto continueTakingInput2;
			}

			ReleaseDC(hWnd, hdc);
			isFirstPress = 1;continueTakingInput2:;
		}
		else if (isThirdPress)
		{
			hdc = GetDC(hWnd);

			s1x = LOWORD(lp);
			s1y = HIWORD(lp);

			if (ch == 13)
			{
				CurveDrawer *curveDrawer = new SecondDegreeCurveDrawer();
				Point startPoint, endPoint;
				startPoint.x = x1;
				startPoint.y = y1;
				endPoint.x = x2;
				endPoint.y = y2;
				Point slopes[1];
				slopes[0].x = s1x;
				slopes[0].y = s1y;
				curveDrawer->drawCurve(hdc, startPoint, endPoint, slopes);
			}
			else
			{
				isThirdPress = 0;
				goto continueTakingInput3;
			}

			ReleaseDC(hWnd, hdc);
			isFirstPress = 1;
			isSecondPress = 1;continueTakingInput3:;
		}
		else
		{
			hdc = GetDC(hWnd);

			s2x = LOWORD(lp);
			s2y = HIWORD(lp);

			if (ch == 14)
			{
				CurveDrawer *curveDrawer = new HermiteCurveDrawer();
				Point startPoint, endPoint;
				startPoint.x = x1;
				startPoint.y = y1;
				endPoint.x = x2;
				endPoint.y = y2;
				Point slopes[2];
				slopes[0].x = s1x;
				slopes[0].y = s1y;
				slopes[1].x = s2x;
				slopes[1].y = s2y;
				curveDrawer->drawCurve(hdc, startPoint, endPoint, slopes);
			}
			else if (ch == 15)
			{
				CurveDrawer *curveDrawer = new BezierCurveDrawer();
				Point startPoint, endPoint;
				startPoint.x = x1;
				startPoint.y = y1;
				endPoint.x = x2;
				endPoint.y = y2;
				Point slopes[2];
				slopes[0].x = s1x;
				slopes[0].y = s1y;
				slopes[1].x = s2x;
				slopes[1].y = s2y;
				curveDrawer->drawCurve(hdc, startPoint, endPoint, slopes);
			}
			else if (ch == 16)
			{
				Point points[4];
				points[0].x = x1;
				points[0].y = y1;
				points[1].x = s1x;
				points[1].y = s1y;
				points[2].x = x2;
				points[2].y = y2;
				points[3].x = s2x;
				points[3].y = s2y;
				HermiteCurveDrawer hermiteCurveDrawer;
				hermiteCurveDrawer.drawSpline(hdc, points, 4, 0.06);
			}
			else if (ch == 17)
			{
				Point points[4];
				points[0].x = x1;
				points[0].y = y1;
				points[1].x = s1x;
				points[1].y = s1y;
				points[2].x = x2;
				points[2].y = y2;
				points[3].x = s2x;
				points[3].y = s2y;
				ConvexFiller convexFiller;
				convexFiller.convexFill(hdc, points, 4);
			}

			ReleaseDC(hWnd, hdc);
			isFirstPress = 1;
			isSecondPress = 1;
			isThirdPress = 1;
		}
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}break;
	default:
		return DefWindowProc(hWnd, mcode, wp, lp);
	}
}


int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstr, int winFormat)
{
	HWND hWnd;
	WNDCLASSEX wndClassEx;
	wndClassEx.cbClsExtra = 0;
	wndClassEx.cbSize = sizeof(wndClassEx);
	wndClassEx.cbWndExtra = 0;
	wndClassEx.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.hInstance = hInst;
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClassEx.lpfnWndProc = MyWindowProcedure;
	wndClassEx.lpszClassName = L"myClass";
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wndClassEx);

	hWnd = CreateWindowEx(0, L"myClass", L"Graphtona", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInst, 0);
	ShowWindow(hWnd, winFormat);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}