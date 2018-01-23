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
	BLACK,
	RED,
	WHITE,
	GRAY
};

void changeBackgroundColor(HWND hWnd, Color newColor) {
	HBRUSH hbrush;
	switch (newColor) {
	case BLACK:
		hbrush = CreateSolidBrush(RGB(0, 0, 0));
		break;
	case RED:
		hbrush = CreateSolidBrush(RGB(255, 0, 0));
		break;
	case WHITE:
		hbrush = CreateSolidBrush(RGB(255, 255, 255));
		break;
	default: // gray color
		hbrush = CreateSolidBrush(RGB(128, 128, 128));
	}	

	HBRUSH holdBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hbrush);
	DeleteObject(holdBrush);
	InvalidateRect(hWnd, NULL, TRUE);
}

enum Option {
	CHANGE_TO_COLOR_1,
	CHANGE_TO_COLOR_2,
	CHANGE_TO_COLOR_3,
	CHANGE_TO_COLOR_4,
	LINE_DDA,
	LINE_PARAMETRIC,
	LINE_BRESENHAM,
	CIRCLE_CARTESIAN,
	CIRCLE_BASIC_POLAR,
	CIRCLE_IMPROVED_POLAR,
	CIRCLE_BRESENHAM,
	ELLIPSE,
	CURVE_FIRST_DEGREE,
	CURVE_SECOND_DEGREE,
	HERMITE,
	BEZIER,
	SPLINE,
	CONVEX_FILLING,
	CIRCLE_FILLING,
	CLIP_POINT_RECTANGLE,
	CLIP_LINE_RECTANGLE,
	CLIP_POINT_CIRCLE,
	CLIP_LINE_CIRCLE
};

HMENU createMenuBar() {
	HMENU hMenuBar = CreateMenu();

	HMENU hFile1 = CreateMenu(); // background color
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile1, L"Change Background color");
	AppendMenu(hFile1, MF_STRING, CHANGE_TO_COLOR_1, L"Black");
	AppendMenu(hFile1, MF_STRING, CHANGE_TO_COLOR_2, L"Red");
	AppendMenu(hFile1, MF_STRING, CHANGE_TO_COLOR_3, L"White");
	AppendMenu(hFile1, MF_STRING, CHANGE_TO_COLOR_4, L"Gray");

	HMENU hFile2 = CreateMenu(); // line
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile2, L"Line");
	AppendMenu(hFile2, MF_STRING, LINE_DDA, L"Simple Line DDA");
	AppendMenu(hFile2, MF_STRING, LINE_PARAMETRIC, L"Parametric line");
	AppendMenu(hFile2, MF_STRING, LINE_BRESENHAM, L"Bresenham midpoint algorithm");

	HMENU hFile3 = CreateMenu(); // circle
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile3, L"Circle");
	AppendMenu(hFile3, MF_STRING, CIRCLE_CARTESIAN, L"Direct Cartesian method");
	AppendMenu(hFile3, MF_STRING, CIRCLE_BASIC_POLAR, L"Polar direct method");
	AppendMenu(hFile3, MF_STRING, CIRCLE_IMPROVED_POLAR, L"Iterative polar algorithm");
	AppendMenu(hFile3, MF_STRING, CIRCLE_BRESENHAM, L"Bresenham midpoint algorithm");

	HMENU hFile7 = CreateMenu(); // ellipse
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile7, L"Ellipse");
	AppendMenu(hFile7, MF_STRING, ELLIPSE, L"Ellipse Drawing");

	HMENU hFile4 = CreateMenu(); // curve
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile4, L"Curve");
	AppendMenu(hFile4, MF_STRING, CURVE_FIRST_DEGREE, L"First Degree");
	AppendMenu(hFile4, MF_STRING, CURVE_SECOND_DEGREE, L"Second Degree");
	AppendMenu(hFile4, MF_STRING, HERMITE, L"Hermite");
	AppendMenu(hFile4, MF_STRING, BEZIER, L"Bezier");
	AppendMenu(hFile4, MF_STRING, SPLINE, L"Spline");

	HMENU hFile5 = CreateMenu(); // convex filling
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile5, L"Filling");
	AppendMenu(hFile5, MF_STRING, CONVEX_FILLING, L"Convex filling");
	AppendMenu(hFile5, MF_STRING, CIRCLE_FILLING, L"Circle filling");

	HMENU hFile6 = CreateMenu(); // clipping
	AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFile6, L"Clipping");
	AppendMenu(hFile6, MF_STRING, CLIP_POINT_RECTANGLE, L"Point according to rectangle");
	AppendMenu(hFile6, MF_STRING, CLIP_LINE_RECTANGLE, L"Line according to rectangle");
	AppendMenu(hFile6, MF_STRING, CLIP_POINT_CIRCLE, L"Point according to circle");
	AppendMenu(hFile6, MF_STRING, CLIP_LINE_CIRCLE, L"Line according to circle");

	return hMenuBar;
}

LPARAM WINAPI MyWindowProcedure(HWND hWnd, UINT mcode, WPARAM wp, LPARAM lp) {
	static int userChoice = -1;
	static double x1, y1, s1x, s1y, x2, y2, s2x, s2y;
	static bool isFirstPress = 1, isSecondPress = 1, isThirdPress = 1;

	switch (mcode) {
	case WM_CREATE: {
		HMENU hMenubar = createMenuBar();
		SetMenu(hWnd, hMenubar);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wp)) {
		case CHANGE_TO_COLOR_1:
		case CHANGE_TO_COLOR_2:
		case CHANGE_TO_COLOR_3:
		case CHANGE_TO_COLOR_4:
			changeBackgroundColor(hWnd, Color(LOWORD(wp)));
			break;
		default: // not a color change choice
			userChoice = LOWORD(wp);
			isFirstPress = 1;
			isSecondPress = 1;
			isThirdPress = 1;
		}
	}break;
	case WM_LBUTTONDOWN: {
		if (isFirstPress) {
			Algorithm::hdc = GetDC(hWnd); // handle of device context

			x1 = LOWORD(lp);
			y1 = HIWORD(lp);

			switch (userChoice) {
			case CLIP_POINT_RECTANGLE: {
				RectangleClipper rectangleClipper;
				rectangleClipper.clipPoint(Point(x1, y1));
			}break;
			case CLIP_POINT_CIRCLE: {
				CircleClipper circleClipper;
				circleClipper.clipPoint(Point(x1, y1));
			}break;
			default: // no drawing yet, continue receiving clicks from user
				isFirstPress = 0;
				goto continueTakingInput1;
			}

			ReleaseDC(hWnd, Algorithm::hdc);
			isFirstPress = 1;continueTakingInput1:;
		}
		else if (isSecondPress) {
			Algorithm::hdc = GetDC(hWnd); // handle of device context

			x2 = LOWORD(lp);
			y2 = HIWORD(lp);

			switch (userChoice) {
			case LINE_DDA: {
				LineDrawer *lineDrawer = new DDALineDrawer();
				lineDrawer->drawLine(Point(x1, y1), Point(x2, y2));
			}break;
			case LINE_PARAMETRIC: {
				LineDrawer *lineDrawer = new ParametricLineDrawer();
				lineDrawer->drawLine(Point(x1, y1), Point(x2, y2));
			}break;
			case LINE_BRESENHAM: {
				LineDrawer *lineDrawer = new BresenhamLineDrawer();
				lineDrawer->drawLine(Point(x1, y1), Point(x2, y2));
			}break;
			case CIRCLE_CARTESIAN: {
				CircleDrawer *circleDrawer = new CartesianCircleDrawer();
				circleDrawer->drawCircle(Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case CIRCLE_BASIC_POLAR: {
				CircleDrawer *circleDrawer = new BasicPolarCircleDrawer();
				circleDrawer->drawCircle(Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case CIRCLE_IMPROVED_POLAR: {
				CircleDrawer *circleDrawer = new ImprovedPolarCircleDrawer();
				circleDrawer->drawCircle(Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case CIRCLE_BRESENHAM: {
				CircleDrawer *circleDrawer = new BresenhamCircleDrawer();
				circleDrawer->drawCircle(Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case CURVE_FIRST_DEGREE: {
				CurveDrawer *curveDrawer = new FirstDegreeCurveDrawer();
				curveDrawer->drawCurve(Point(x1, y1), Point(x2, y2), {});
			}break;
			case CIRCLE_FILLING: {
				ConvexFiller convexFiller;
				convexFiller.fillCircle(Point(x1, y1), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case ELLIPSE: {
				EllipseDrawer ellipseDrawer;
				ellipseDrawer.drawEllipse(Point(x1, y1), 2 * sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)), sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			}break;
			case CLIP_LINE_RECTANGLE: {
				RectangleClipper rectangleClipper;
				rectangleClipper.clipLine(Point(x1, y1), Point(x2, y2));
			}break;
			case CLIP_LINE_CIRCLE: {
				CircleClipper circleClipper;
				circleClipper.clipLine(Point(x1, y1), Point(x2, y2));
			}break;
			default: // no drawing yet, continue receiving clicks from user
				isSecondPress = 0;
				goto continueTakingInput2;
			}

			ReleaseDC(hWnd, Algorithm::hdc);
			isFirstPress = 1;continueTakingInput2:;
		}
		else if (isThirdPress) {
			Algorithm::hdc = GetDC(hWnd); // handle of device context

			s1x = LOWORD(lp);
			s1y = HIWORD(lp);

			switch (userChoice) {
			case CURVE_SECOND_DEGREE: {
				CurveDrawer *curveDrawer = new SecondDegreeCurveDrawer();
				Point slopes[] = { Point(s1x, s1y) };
				curveDrawer->drawCurve(Point(x1, y1), Point(x2, y2), slopes);
			}break;
			default: // no drawing yet, continue receiving clicks from user
				isThirdPress = 0;
				goto continueTakingInput3;
			}

			ReleaseDC(hWnd, Algorithm::hdc);
			isFirstPress = 1;
			isSecondPress = 1;continueTakingInput3:;
		}
		else {
			Algorithm::hdc = GetDC(hWnd); // handle of device context
			
			s2x = LOWORD(lp);
			s2y = HIWORD(lp);

			switch (userChoice) {
			case HERMITE: {
				CurveDrawer *curveDrawer = new HermiteCurveDrawer();
				Point slopes[] = { Point(s1x, s1y), Point(s2x, s2y) };
				curveDrawer->drawCurve(Point(x1, y1), Point(x2, y2), slopes);
			}break;
			case BEZIER: {
				CurveDrawer *curveDrawer = new BezierCurveDrawer();
				Point slopes[] = { Point(s1x, s1y), Point(s2x, s2y) };
				curveDrawer->drawCurve(Point(x1, y1), Point(x2, y2), slopes);
			}break;
			case SPLINE: {
				Point points[] = { Point(x1, y1), Point(s1x, s1y), Point(x2, y2), Point(s2x, s2y) };
				HermiteCurveDrawer hermiteCurveDrawer;
				hermiteCurveDrawer.drawSpline(points, 4, 0.06);
			}break;
			case CONVEX_FILLING: {
				Point points[] = { Point(x1, y1), Point(s1x, s1y), Point(x2, y2), Point(s2x, s2y) };
				ConvexFiller convexFiller;
				convexFiller.convexFill(points, 4);
			}
			}

			ReleaseDC(hWnd, Algorithm::hdc);
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

WNDCLASSEX prepareWindowClass(HINSTANCE hInst) {
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

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstr, int winFormat) {
	HWND hWnd;

	WNDCLASSEX wndClassEx = prepareWindowClass(hInst);
	RegisterClassEx(&wndClassEx);

	hWnd = CreateWindowEx(0, L"graphtonaWindowClass", L"Graphtona", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInst, 0);
	ShowWindow(hWnd, winFormat);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}
