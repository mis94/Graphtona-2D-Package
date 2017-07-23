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
	black,
	red,
	white,
	gray
};

void changeBackgroundColor(HWND hWnd, Color newColor)
{
	HBRUSH hbrush;
	if (newColor == black)
		hbrush = CreateSolidBrush(RGB(0, 0, 0));
	else if (newColor == red)
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
	else if (newColor == white)
		hbrush = CreateSolidBrush(RGB(255, 255, 255));
	else
		hbrush = CreateSolidBrush(RGB(128, 128, 128));

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}

enum Option {
	changeToColor1,
	changeToColor2,
	changeToColor3,
	changeToColor4,
	ddaLine,
	parametricLine,
	bresenhamLine,
	cartesianCircle,
	basicPolarCircle,
	improvedPolarCircle,
	bresenhamCircle,
	ellipse,
	firstDegree,
	secondDegree,
	hermite,
	bezier,
	spline,
	convexFilling,
	circleFilling,
	clipPointRectangle,
	clipLineRectangle,
	clipPointCircle,
	clipLineCircle
};

HMENU createMenuBar()
{
	HMENU hMenuBar = CreateMenu();

	HMENU hFile1 = CreateMenu(); // background color
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile1, L"Change Background color");
	AppendMenu(hFile1, MF_STRING, changeToColor1, L"Black");
	AppendMenu(hFile1, MF_STRING, changeToColor2, L"Red");
	AppendMenu(hFile1, MF_STRING, changeToColor3, L"White");
	AppendMenu(hFile1, MF_STRING, changeToColor4, L"Gray");

	HMENU hFile2 = CreateMenu(); // line
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile2, L"Line");
	AppendMenu(hFile2, MF_STRING, ddaLine, L"Simple Line DDA");
	AppendMenu(hFile2, MF_STRING, parametricLine, L"Parametric line");
	AppendMenu(hFile2, MF_STRING, bresenhamLine, L"Bresenham midpoint algorithm");

	HMENU hFile3 = CreateMenu(); // circle
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile3, L"Circle");
	AppendMenu(hFile3, MF_STRING, cartesianCircle, L"Direct Cartesian method");
	AppendMenu(hFile3, MF_STRING, basicPolarCircle, L"Polar direct method");
	AppendMenu(hFile3, MF_STRING, improvedPolarCircle, L"Iterative polar algorithm");
	AppendMenu(hFile3, MF_STRING, bresenhamCircle, L"Bresenham midpoint algorithm");

	HMENU hFile7 = CreateMenu(); // ellipse
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile7, L"Ellipse");
	AppendMenu(hFile7, MF_STRING, ellipse, L"Ellipse Drawing");

	HMENU hFile4 = CreateMenu(); // curve
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile4, L"Curve");
	AppendMenu(hFile4, MF_STRING, firstDegree, L"First Degree");
	AppendMenu(hFile4, MF_STRING, secondDegree, L"Second Degree");
	AppendMenu(hFile4, MF_STRING, hermite, L"Hermite");
	AppendMenu(hFile4, MF_STRING, bezier, L"Bezier");
	AppendMenu(hFile4, MF_STRING, spline, L"Spline");

	HMENU hFile5 = CreateMenu(); // convex filling
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile5, L"Filling");
	AppendMenu(hFile5, MF_STRING, convexFilling, L"Convex filling");
	AppendMenu(hFile5, MF_STRING, circleFilling, L"Circle filling");

	HMENU hFile6 = CreateMenu(); // clipping
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile6, L"Clipping");
	AppendMenu(hFile6, MF_STRING, clipPointRectangle, L"Point according to rectangle");
	AppendMenu(hFile6, MF_STRING, clipLineRectangle, L"Line according to rectangle");
	AppendMenu(hFile6, MF_STRING, clipPointCircle, L"Point according to circle");
	AppendMenu(hFile6, MF_STRING, clipLineCircle, L"Line according to circle");

	return hMenuBar;
}

LPARAM WINAPI MyWindowProcedure(HWND hWnd, UINT mcode, WPARAM wp, LPARAM lp)
{
	HDC hdc; //handle of device context
	static int ch = -1;
	static double x1, y1, s1x, s1y, x2, y2, s2x, s2y;
	static bool isFirstPress = 1, isSecondPress = 1, isThirdPress = 1;

	switch (mcode) {
	case WM_CREATE: {
		HMENU hMenubar = createMenuBar();
		SetMenu(hWnd, hMenubar);
	}break;
	case WM_COMMAND:
	{
		if (LOWORD(wp) == changeToColor1)
			changeBackgroundColor(hWnd, black);
		else if (LOWORD(wp) == changeToColor2)
			changeBackgroundColor(hWnd, red);
		else if (LOWORD(wp) == changeToColor3)
			changeBackgroundColor(hWnd, white);
		else if (LOWORD(wp) == changeToColor4)
			changeBackgroundColor(hWnd, gray);
		else if (LOWORD(wp) == ddaLine)
			ch = ddaLine;
		else if (LOWORD(wp) == parametricLine)
			ch = parametricLine;
		else if (LOWORD(wp) == bresenhamLine)
			ch = bresenhamLine;
		else if (LOWORD(wp) == cartesianCircle)
			ch = cartesianCircle;
		else if (LOWORD(wp) == basicPolarCircle)
			ch = basicPolarCircle;
		else if (LOWORD(wp) == improvedPolarCircle)
			ch = improvedPolarCircle;
		else if (LOWORD(wp) == bresenhamCircle)
			ch = bresenhamCircle;
		else if (LOWORD(wp) == firstDegree)
			ch = firstDegree;
		else if (LOWORD(wp) == secondDegree)
			ch = secondDegree;
		else if (LOWORD(wp) == hermite)
			ch = hermite;
		else if (LOWORD(wp) == bezier)
			ch = bezier;
		else if (LOWORD(wp) == spline)
			ch = spline;
		else if (LOWORD(wp) == convexFilling)
			ch = convexFilling;
		else if (LOWORD(wp) == clipPointRectangle)
			ch = clipPointRectangle;
		else if (LOWORD(wp) == clipLineRectangle)
			ch = clipLineRectangle;
		else if (LOWORD(wp) == clipPointCircle)
			ch = clipPointCircle;
		else if (LOWORD(wp) == clipLineCircle)
			ch = clipLineCircle;
		else if (LOWORD(wp) == circleFilling)
			ch = circleFilling;
		else if (LOWORD(wp) == ellipse)
			ch = ellipse;

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

			if (ch == clipPointRectangle)
			{
				RectangleClipper rectangleClipper(hdc);
				rectangleClipper.clipPoint(hdc, Point(x1, y1));
			}
			else if (ch == clipPointCircle)
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

			if (ch == ddaLine)
			{
				LineDrawer *lineDrawer = new DDALineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == parametricLine)
			{
				LineDrawer *lineDrawer = new ParametricLineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == bresenhamLine)
			{
				LineDrawer *lineDrawer = new BresenhamLineDrawer();
				lineDrawer->drawLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == cartesianCircle)
			{
				CircleDrawer *circleDrawer = new CartesianCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == basicPolarCircle)
			{
				CircleDrawer *circleDrawer = new BasicPolarCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == improvedPolarCircle)
			{
				CircleDrawer *circleDrawer = new ImprovedPolarCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == bresenhamCircle)
			{
				CircleDrawer *circleDrawer = new BresenhamCircleDrawer();
				circleDrawer->drawCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == firstDegree)
			{
				CurveDrawer *curveDrawer = new FirstDegreeCurveDrawer();
				curveDrawer->drawCurve(hdc, Point(x1, y1), Point(x2, y2), {});
			}
			else if (ch == circleFilling)
			{
				ConvexFiller convexFiller;
				convexFiller.fillCircle(hdc, Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == ellipse)
			{
				EllipseDrawer ellipseDrawer;
				ellipseDrawer.drawEllipse(hdc, Point(x1, y1), 2 * sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}
			else if (ch == clipLineRectangle)
			{
				RectangleClipper rectangleClipper(hdc);
				rectangleClipper.clipLine(hdc, Point(x1, y1), Point(x2, y2));
			}
			else if (ch == clipLineCircle)
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

			if (ch == secondDegree)
			{
				CurveDrawer *curveDrawer = new SecondDegreeCurveDrawer();
				Point slopes[] = { Point(s1x, s1y) };
				curveDrawer->drawCurve(hdc, Point(x1, y1), Point(x2, y2), slopes);
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

			if (ch == hermite)
			{
				CurveDrawer *curveDrawer = new HermiteCurveDrawer();
				Point slopes[] = {Point(s1x, s1y), Point(s2x, s2y)};
				curveDrawer->drawCurve(hdc, Point(x1, y1), Point(x2, y2), slopes);
			}
			else if (ch == bezier)
			{
				CurveDrawer *curveDrawer = new BezierCurveDrawer();
				Point slopes[] = { Point(s1x, s1y), Point(s2x, s2y) };
				curveDrawer->drawCurve(hdc, Point(x1, y1), Point(x2, y2), slopes);
			}
			else if (ch == spline)
			{
				Point points[] = { Point(x1, y1), Point(s1x, s1y), Point(x2, y2), Point(s2x, s2y) };
				HermiteCurveDrawer hermiteCurveDrawer;
				hermiteCurveDrawer.drawSpline(hdc, points, 4, 0.06);
			}
			else if (ch == convexFilling)
			{
				Point points[] = { Point(x1, y1), Point(s1x, s1y), Point(x2, y2), Point(s2x, s2y) };
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

WNDCLASSEX prepareWindowClass(HINSTANCE hInst)
{
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
	wndClassEx.lpszClassName = L"graphtonaWindowClass";
	wndClassEx.lpszMenuName = NULL;
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	return wndClassEx;
}

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstr, int winFormat)
{
	HWND hWnd;

	WNDCLASSEX wndClassEx = prepareWindowClass(hInst);
	RegisterClassEx(&wndClassEx);

	hWnd = CreateWindowEx(0, L"graphtonaWindowClass", L"Graphtona", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInst, 0);
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