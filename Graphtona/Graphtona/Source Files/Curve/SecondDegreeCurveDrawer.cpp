#include "..\..\Header Files\Curve\SecondDegreeCurveDrawer.h"

void SecondDegreeCurveDrawer::drawCurve(Point startPoint, Point endPoint, Point slopes[])
{
	double beta1 = startPoint.x;
	double beta2 = startPoint.y;
	double alpha1 = slopes[0].x - startPoint.x;
	double alpha2 = slopes[0].y - startPoint.y;
	double gamma1 = endPoint.x;
	double gamma2 = endPoint.y;

	double dt = 1 / max(abs(alpha1), abs(alpha2));

	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(abs(alpha1), abs(alpha2)))
	{
		x = alpha1*t*t + beta1*t + gamma1;
		y = alpha2*t*t + beta2*t + gamma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}