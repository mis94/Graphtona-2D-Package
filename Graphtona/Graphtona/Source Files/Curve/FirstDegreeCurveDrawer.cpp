#include "..\..\Header Files\Curve\FirstDegreeCurveDrawer.h"

void FirstDegreeCurveDrawer::drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[])
{
	double beta1 = startPoint.x;
	double beta2 = startPoint.y;
	double alpha1 = endPoint.x - startPoint.x;
	double alpha2 = endPoint.y - startPoint.y;

	double dt = 1 / max(abs(alpha1), abs(alpha2));

	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(abs(alpha1), abs(alpha2)))
	{
		x = alpha1*t + beta1;
		y = alpha2*t + beta2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}