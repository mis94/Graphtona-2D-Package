#include "..\..\Header Files\Curve\HermiteCurveDrawer.h"

void HermiteCurveDrawer::drawCurve(Point startPoint, Point endPoint, Point slopes[])
{
	int hermiteMatrix[4][4] = { { 2, 1, -2, 1 },{ -3, -2, 3, -1 },{ 0, 1, 0, 0 },{ 1, 0, 0, 0 } };
	int inputX[4] = { startPoint.x, slopes[0].x, endPoint.x, slopes[1].x };
	int inputY[4] = { startPoint.y, slopes[0].y, endPoint.y, slopes[1].y };
	// each row in the matrix with the vector of xs and ys
	double alpha1 = mulitplyTwoVectors(hermiteMatrix[0], inputX, 4), alpha2 = mulitplyTwoVectors(hermiteMatrix[0], inputY, 4);
	double beta1 = mulitplyTwoVectors(hermiteMatrix[1], inputX, 4), beta2 = mulitplyTwoVectors(hermiteMatrix[1], inputY, 4);
	double gamma1 = mulitplyTwoVectors(hermiteMatrix[2], inputX, 4), gamma2 = mulitplyTwoVectors(hermiteMatrix[2], inputY, 4);
	double sigma1 = mulitplyTwoVectors(hermiteMatrix[3], inputX, 4), sigma2 = mulitplyTwoVectors(hermiteMatrix[3], inputY, 4);

	double dt = 1 / max(abs((double)endPoint.y - (double)startPoint.y), abs((double)endPoint.x - (double)startPoint.x));
	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(abs((double)endPoint.y - (double)startPoint.y), abs((double)endPoint.x - (double)startPoint.x)))
	{
		x = alpha1*(t*t*t) + beta1*(t*t) + gamma1*(t)+sigma1;
		y = alpha2*(t*t*t) + beta2*(t*t) + gamma2*(t)+sigma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}

void HermiteCurveDrawer::drawSpline(Point points[], int numberOfPoints, double c) // c is the tension of the curve (0---1)
{
	double s1x = (1 - c)*(points[2].x - points[0].x); // slope at Pi
	double s1y = (1 - c)*(points[2].y - points[0].y);

	for (int i = 2;i < numberOfPoints - 1;i++)
	{
		double s2x = (1 - c)*(points[i + 1].x - points[i - 1].x);
		double s2y = (1 - c)*(points[i + 1].y - points[i - 1].y);

		Point slopes[2] = {Point(s1x, s1y), Point(s2x, s2y)};

		drawCurve(Point(points[i - 1].x, points[i - 1].y), Point(points[i].x, points[i].y), slopes);

		s1x = s2x;
		s1y = s2y;
	}
}