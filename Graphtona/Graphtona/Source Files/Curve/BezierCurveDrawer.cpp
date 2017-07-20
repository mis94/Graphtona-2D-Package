#include "..\..\Header Files\Curve\BezierCurveDrawer.h"

void BezierCurveDrawer::drawCurve(HDC hdc, Point startPoint, Point endPoint, Point slopes[])
{
	int bezierMatrix[4][4] = { { -1, 3, -3, 1 },{ 3, -6, 3, 0 },{ -3, 3, 0, 0 },{ 1, 0, 0, 0 } };
	int inputX[4] = { startPoint.x, slopes[0].x, endPoint.x, slopes[1].x };
	int inputY[4] = { startPoint.y, slopes[0].y, endPoint.y, slopes[1].y };

	// each row in the matrix with the vector of xs and ys
	double alpha1 = mulitplyTwoVectors(bezierMatrix[0], inputX, 4), alpha2 = mulitplyTwoVectors(bezierMatrix[0], inputY, 4);
	double beta1 = mulitplyTwoVectors(bezierMatrix[1], inputX, 4), beta2 = mulitplyTwoVectors(bezierMatrix[1], inputY, 4);
	double gamma1 = mulitplyTwoVectors(bezierMatrix[2], inputX, 4), gamma2 = mulitplyTwoVectors(bezierMatrix[2], inputY, 4);
	double sigma1 = mulitplyTwoVectors(bezierMatrix[3], inputX, 4), sigma2 = mulitplyTwoVectors(bezierMatrix[3], inputY, 4);

	double dt = 1 / max(abs(endPoint.y - startPoint.y), abs(endPoint.x - startPoint.x));
	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(abs(endPoint.y - startPoint.y), abs(endPoint.x - startPoint.x)))
	{
		x = alpha1*(t*t*t) + beta1*(t*t) + gamma1*(t)+sigma1;
		y = alpha2*(t*t*t) + beta2*(t*t) + gamma2*(t)+sigma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}