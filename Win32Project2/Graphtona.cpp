#include "stdafx.h" // if any more headers need to be included add them to this file
using namespace std;

const double PI = 3.14159265359;

double absoluteDouble(double number)
{
	if (number < 0.0)
		return number*-1;
	else
		return number;
}

void swapInteger(int &x, int &y)
{
	/*x = x^y;
	y = x^y;
	x = x^y;*/
	int temp = x;
	x = y;
	y = temp;
}

void swapDouble(double &x, double &y)
{
	double temp = x;
	x = y;
	y = temp;
}

void drawLineMethod1(HDC hdc ,double xs, double ys, double xe, double ye) // using simple parametric equation
{
	double dt = 1 / max(absoluteDouble(xs-xe), absoluteDouble(ys-ye)); // we can also cast (xs-xe) and (ys-ye) to integer and it will work
	for (double t = 0;t <= 1;t += dt)
	{
		double x = xs + t*(xe - xs);
		double y = ys + t*(ye - ys);
		SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
	}
}

void drawLineMethod2(HDC hdc, double xs, double ys, double xe, double ye) // using optimized parametric equation
{
	int numberOfPoints = max((int)(xs - xe), (int)(ys - ye));
	double dt = 1.0 / numberOfPoints;
	double x = xs, y = ys;
	double dx = dt*(xe - xs);
	double dy = dt*(ye - ys);
	for (double t = 1;t <= numberOfPoints;t++)
	{
		SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		x += dx;
		y += dy;
	}
}

void drawLineDDA(HDC hdc, double xs, double ys, double xe, double ye)
{
	double dx = xe - xs;
	double dy = ye - ys;

	if (absoluteDouble(dy) < absoluteDouble(dx)) // slope < 1, x is the independent variable
	{
		double slope = dy / dx;

		if (xs > xe)
		{
			swapDouble(xs, xe);
			swapDouble(ys, ye);
		}

		int x = xs;
		double y = ys;
		SetPixel(hdc, x, y, RGB(max(x+y, 255), x, y));

		while (x < xe)
		{
			x++;
			y += slope;
			SetPixel(hdc, x, y, RGB(x, max(x + y, 255), y));
		}
	}
	else // slope > 1, y is the independent variable
	{
		double slope = dx / dy;

		if (ys > ye)
		{
			swapDouble(xs, xe);
			swapDouble(ys, ye);
		}

		double x = xs;
		int y = ys;
		SetPixel(hdc, x, y, RGB(y, x, max(x + y, 255)));

		while (y < ye)
		{
			y++;
			x += slope;
			SetPixel(hdc, x, y, RGB(y, max(x + y, 255), x));
		}
	}
}

void drawDirectLine(HDC hdc, double xs, double ys, double xe, double ye)
{
	double dy = ye - ys;
	double dx = xe - xs;
	double slope = dy / dx;

	if (slope < 1)
	{
		if (xe < xs)
		{
			swapDouble(xs, xe);
			swapDouble(ys, ye);
		}
		double x = xs;
		double y = ys;
		while (x < xe)
		{
			x++;
			y = ys + slope * (x - xs);
			SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		}
	}
	else
	{
		if (ye < ys)
		{
			swapDouble(xs, xe);
			swapDouble(ys, ye);
		}
		double x = xs;
		double y = ys;
		while (y < ye)
		{
			y++;
			x = xs + (y - ys) / slope;
			SetPixel(hdc, round(x), round(y), RGB(0, 0, 0));
		}
	}
}

void drawLineBresenham(HDC hdc, int xs, int ys, int xe, int ye)
{
	int deltaX = xe - xs;
	int deltaY = ye - ys;
	
	if (abs(deltaY) <= abs(deltaX))
	{
		if (xs > xe)
		{
			swapInteger(xs, xe);
			swapInteger(ys, ye);
			deltaX = abs(deltaX);
			deltaY = abs(deltaY);
		}

		int error = 2 * deltaY - deltaX;
		int d1 = 2 * deltaY;
		int d2 = 2 * (deltaY - deltaX);

		int x = xs;
		int y = ys;

		int increment;
		if (ys < ye)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (x < xe)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				y += increment;
			}
			x++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
	else
	{
		if (ys > ye)
		{
			swapInteger(xs, xe);
			swapInteger(ys, ye);
			deltaX = abs(deltaX);
			deltaY = abs(deltaY);
		}

		int error = 2 * deltaX - deltaY;
		int d1 = 2 * deltaX;
		int d2 = 2 * (deltaX - deltaY);

		int x = xs;
		int y = ys;

		int increment;
		if (xs < xe)
			increment = 1;
		else
			increment = -1;

		SetPixel(hdc, x, y, RGB(0, 0, 0));
		while (y < ye)
		{
			if (error < 0)
				error += d1;
			else
			{
				error += d2;
				x += increment;
			}
			y++;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
	}
}

void draw8Points(HDC hdc, double xc, double yc, int a, int b)
{
	SetPixel(hdc, xc + a, yc + b, RGB(0, 0, 0));
	SetPixel(hdc, xc - a, yc + b, RGB(0, 0, 0));
	SetPixel(hdc, xc + a, yc - b, RGB(0, 0, 0));
	SetPixel(hdc, xc - a, yc - b, RGB(0, 0, 0));
	SetPixel(hdc, xc + b, yc + a, RGB(0, 0, 0));
	SetPixel(hdc, xc - b, yc + a, RGB(0, 0, 0));
	SetPixel(hdc, xc + b, yc - a, RGB(0, 0, 0));
	SetPixel(hdc, xc - b, yc - a, RGB(0, 0, 0));
}

void drawCircleImprovedPolar(HDC hdc, double xc, double yc, int radius)
{
	double dtheta = 1.0 / radius;
	double ct = cos(dtheta);
	double st = sin(dtheta);

	double x = radius;
	double y = 0;

	draw8Points(hdc, xc, yc, round(x), round(y));

	while (y < x)
	{
		double x1 = x*ct - y*st;
		y = x*st + y*ct;
		x = x1;
		draw8Points(hdc, xc, yc, round(x), round(y));
	}
}

void drawCircleDirectCatesian(HDC hdc, double xc, double yc, int radius)
{
	double x = 0;
	double y = radius;

	while (x < y)
	{
		draw8Points(hdc, xc, yc, round(x), round(y));
		x = x + 1;
		y = sqrt(radius*radius - x*x);
	}
}

void drawCircleBasicPolar(HDC hdc, double xc, double yc, int radius)
{
	double dtheta = 1.0 / radius;
	double x, y;
	for (double theta = 0;theta < PI / 4;theta += dtheta)
	{
		x = radius*cos(theta);
		y = radius*sin(theta);
		draw8Points(hdc, xc, yc, round(x), round(y));
	}
}

void drawCircleBresenham(HDC hdc, double xc, double yc, int radius)
{
	int x = 0;
	int y = radius;

	draw8Points(hdc, xc, yc, x, y);

	int d = 1 - radius; // 5/4 in the lecture
	int d1 = 3;
	int d2 = 5 - (2 * radius);

	while (x < y)
	{
		if (d < 0)
		{
			d += d1;
			d2 += 2;
		}
		else
		{
			d += d2;
			d2 += 4;
			y--;
		}
		x++;
		d1 += 2;
		draw8Points(hdc, xc, yc, x, y);
	}
}

void drawFirstDegreeCurve(HDC hdc, double xs, double ys, double xe, double ye)
{
	double beta1 = xs;
	double beta2 = ys;
	double alpha1 = xe - xs;
	double alpha2 = ye - ys;
	
	double dt = 1 / max(absoluteDouble(alpha1), absoluteDouble(alpha2));

	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(absoluteDouble(alpha1), absoluteDouble(alpha2)))
	{
		x = alpha1*t + beta1;
		y = alpha2*t + beta2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}

void drawSecondDegreeCurve(HDC hdc, double xs, double ys, double xe, double ye, double s1x, double s1y)
{
	double beta1 = xs;
	double beta2 = ys;
	double alpha1 = xe - xs;
	double alpha2 = ye - ys;
	double gamma1 = s1x;
	double gamma2 = s1y;

	double dt = 1 / max(absoluteDouble(alpha1), absoluteDouble(alpha2));

	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(absoluteDouble(alpha1), absoluteDouble(alpha2)))
	{
		x = alpha1*t*t + beta1*t + gamma1;
		y = alpha2*t*t + beta2*t + gamma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}

int mulitplyTwoVectors(int v1[], int v2[], int size)
{
	int ret = 0;
	for (int i = 0;i < size;i++)
		ret += v1[i] * v2[i];
	return ret;
}

void drawHermiteCurve(HDC hdc, double xs, double ys, double s1x, double s1y, double xe, double ye, double s2x, double s2y)
{
	int hermiteMatrix[4][4] = { {2, 1, -2, 1}, {-3, -2, 3, -1}, {0, 1, 0, 0}, {1, 0, 0, 0} };
	int inputX[4] = { xs, s1x, xe, s2x };
	int inputY[4] = { ys, s1y, ye, s2y };
	// each row in the matrix with the vector of xs and ys
	double alpha1 = mulitplyTwoVectors(hermiteMatrix[0], inputX, 4), alpha2 = mulitplyTwoVectors(hermiteMatrix[0], inputY, 4);
	double beta1 = mulitplyTwoVectors(hermiteMatrix[1], inputX, 4), beta2 = mulitplyTwoVectors(hermiteMatrix[1], inputY, 4);
	double gamma1 = mulitplyTwoVectors(hermiteMatrix[2], inputX, 4), gamma2 = mulitplyTwoVectors(hermiteMatrix[2], inputY, 4);
	double sigma1 = mulitplyTwoVectors(hermiteMatrix[3], inputX, 4), sigma2 = mulitplyTwoVectors(hermiteMatrix[3], inputY, 4);

	double dt = 1 / max(absoluteDouble(ye - ys), absoluteDouble(xe - xs));
	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(absoluteDouble(ye - ys), absoluteDouble(xe - xs)))
	{
		x = alpha1*(t*t*t) + beta1*(t*t) + gamma1*(t)+sigma1;
		y = alpha2*(t*t*t) + beta2*(t*t) + gamma2*(t)+sigma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}

void drawBezierCurve(HDC hdc, double xs, double ys, double s1x, double s1y, double xe, double ye, double s2x, double s2y)
{
	int bezierMatrix[4][4] = { { -1, 3, -3, 1 },{ 3, -6, 3, 0 },{ -3, 3, 0, 0 },{ 1, 0, 0, 0 } };
	int inputX[4] = { xs, s1x, xe, s2x };
	int inputY[4] = { ys, s1y, ye, s2y };

	// each row in the matrix with the vector of xs and ys
	double alpha1 = mulitplyTwoVectors(bezierMatrix[0], inputX, 4), alpha2 = mulitplyTwoVectors(bezierMatrix[0], inputY, 4);
	double beta1 = mulitplyTwoVectors(bezierMatrix[1], inputX, 4), beta2 = mulitplyTwoVectors(bezierMatrix[1], inputY, 4);
	double gamma1 = mulitplyTwoVectors(bezierMatrix[2], inputX, 4), gamma2 = mulitplyTwoVectors(bezierMatrix[2], inputY, 4);
	double sigma1 = mulitplyTwoVectors(bezierMatrix[3], inputX, 4), sigma2 = mulitplyTwoVectors(bezierMatrix[3], inputY, 4);

	double dt = 1 / max(absoluteDouble(ye - ys), absoluteDouble(xe - xs));
	double x, y;
	double t = 0;
	int i = 0;
	while (i <= max(absoluteDouble(ye - ys), absoluteDouble(xe - xs)))
	{
		x = alpha1*(t*t*t) + beta1*(t*t) + gamma1*(t)+sigma1;
		y = alpha2*(t*t*t) + beta2*(t*t) + gamma2*(t)+sigma2;
		SetPixel(hdc, x, y, RGB(0, 0, 0));
		t += dt;
		i++;
	}
}

void drawSplines(HDC hdc, POINT points[], int numberOfPoints, double c) // c is the tension of the curve (0---1)
{
	double s1x = (1 - c)*(points[2].x - points[0].x); // slope at Pi
	double s1y = (1 - c)*(points[2].y - points[0].y);

	for (int i = 2;i < numberOfPoints - 1;i++)
	{
		double s2x = (1 - c)*(points[i+1].x - points[i-1].x);
		double s2y = (1 - c)*(points[i+1].y - points[i-1].y);
		drawHermiteCurve(hdc, points[i - 1].x, points[i - 1].y, s1x, s1y, points[i].x, points[i].y, s2x, s2y);
		s1x = s2x;
		s1y = s2y;
	}
}

void drawRhombus(HDC hdc, double xs, double ys, double xe, double ye)
{
	double distance_x = absoluteDouble(xe - xs);
	double distance_y = absoluteDouble(ye - ys);
	
	drawLineDDA(hdc, xs, ys, xs + distance_x , ys - distance_y);
	drawLineDDA(hdc , xs + distance_x, ys - distance_y , xs , ys - distance_y - distance_y);
	drawLineDDA(hdc, xs - distance_x, ys - distance_y , xs, ys - distance_y - distance_y);
	drawLineDDA(hdc, xs, ys, xs - distance_x, ys - distance_y);
}

void drawRectangle(HDC hdc, double xs, double ys, double xe, double ye)
{
	double distance_x = absoluteDouble(xe - xs);
	double distance_y = absoluteDouble(ye - ys);
	if (xs < xe)
	{
		swapDouble(xs, xe);
		swapDouble(ys, ye);
	}
	if (distance_y == 0)
		distance_y = 150;
	drawLineMethod1(hdc, xs, ys, xe, ye);
	drawLineMethod1(hdc, xe, ye, xe, ye + distance_y);
	drawLineMethod1(hdc, xe, ye + distance_y, xs, ys + distance_y);
	drawLineMethod1(hdc, xs, ys+distance_y, xs, ys);
}

void drawTriangle(HDC hdc, double xs, double ys, double xe, double ye)
{
	double distance_x = absoluteDouble(xe - xs);
	double distance_y = absoluteDouble(ye - ys);
	if (xs < xe)
	{
		swapDouble(xs, xe);
		swapDouble(ys, ye);
	}
	drawLineMethod1(hdc, xs, ys, xe, ye);
	drawLineMethod1(hdc, xs, ys, xs + distance_x / 2, ys + distance_y / 2);
	drawLineMethod1(hdc, xe, ye, xs + distance_x / 2, ys + distance_y / 2);
}

/*

#include <list>
using namespace std;
#define MAXENTRIES 600
struct EdgeRec
{
double x;
double minv;
int ymax;
bool operator<(EdgeRec r)
{
return x<r.x;
}
};
typedef list<EdgeRec> EdgeList;

EdgeRec InitEdgeRec(POINT& v1,POINT& v2)
{
if(v1.y>v2.y)swap(v1,v2);
EdgeRec rec;
rec.x=v1.x;
rec.ymax=v2.y;
rec.minv=(double)(v2.x-v1.x)/(v2.y-v1.y);
return rec;
}

void InitEdgeTable(POINT *polygon,int n,EdgeList table[])
{
POINT v1=polygon[n-1];
for(int i=0;i<n;i++)
{
POINT v2=polygon[i];
if(v1.y==v2.y){v1=v2;continue;}
EdgeRec rec=InitEdgeRec(v1, v2);
table[v1.y].push_back(rec);
v1=polygon[i];
}
}

void GeneralPolygonFill(HDC hdc,POINT *polygon,int n,COLORREF c)
{
EdgeList *table=new EdgeList [MAXENTRIES];
InitEdgeTable(polygon,n,table);
int y=0;
while(y<MAXENTRIES && table[y].size()==0)y++;
if(y==MAXENTRIES)return;
EdgeList ActiveList=table[y];
while (ActiveList.size()>0)
{
ActiveList.sort();
for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
{
int x1=(int)ceil(it->x);
it++;
int x2=(int)floor(it->x);
for(int x=x1;x<=x2;x++)SetPixel(hdc,x,y,c);
}
y++;
EdgeList::iterator it=ActiveList.begin();
while(it!=ActiveList.end())
if(y==it->ymax) it=ActiveList.erase(it); else it++;
for(EdgeList::iterator it=ActiveList.begin();it!=ActiveList.end();it++)
it->x+=it->minv;
ActiveList.insert(ActiveList.end(),table[y].begin(),table[y].end());
}
delete[] table;
}

*/

struct EdgeRec {
	int xLeft, xRight;
	EdgeRec()
	{
		xLeft = INT_MAX;
		xRight = INT_MIN;
	}
	EdgeRec(int x1, int x2)
	{
		xLeft = x1;
		xRight = x2;
	}
};

void convexFill(HDC hdc, POINT* points, int numberOfPoints)
{
	EdgeRec *table = new EdgeRec[800];
	POINT v1 = points[numberOfPoints - 1];
	for (int i = 0;i < numberOfPoints;i++)
	{
		POINT v2 = points[i];
		if (v1.y == v2.y)
			goto horizontal;
		if (v1.y > v2.y)
			swap(v1, v2);
		int y = v1.y;
		double x = v1.x;
		double mi = (v2.x - v1.x) / (double)(v2.y - v1.y);
		while (y < v2.y)
		{
			if (x < table[y].xLeft)
				table[y].xLeft = ceil(x);
			if (x > table[y].xRight)
				table[y].xRight = floor(x);
			x += mi;
			y++;
		}
		horizontal:v1 = points[i];
	}
	
	for (int i = 0;i < 800;i++)
	{
		if (table[i].xLeft < table[i].xRight)
			drawLineDDA(hdc, table[i].xLeft, i, table[i].xRight, i);
	}
}

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

int Wtop = 60, Wbottom = 500, Wleft = 60, Wright = 500;

void clipPoint(HDC hdc, int xs, int ys, int xleft, int xright, int ytop, int ybottom)
{
	if (xs <= xright&&xs >= xleft)
	{
		if (ys >= ytop&&ys <= ybottom)
			SetPixel(hdc, xs, ys, RGB(0, 0, 0));
	}
}

union OutCode {

	unsigned All : 4;
	struct {
		unsigned left : 1, top : 1, right : 1, bottom : 1;
	};
};

OutCode getOutCode(double x, double y, int xleft, int xright, int ytop, int ybottom) 
{
	OutCode out;
	out.All = 0;
	if (x < xleft)
		out.left = 1;
	else if (x>xright)
		out.right = 1;

	if (y<ytop)
		out.top = 1;
	if (y>ybottom)
		out.bottom = 1;
	return out;
}

void verticalIntersect(double xs, double ys, double xe, double ye, int x, double *xi, double *yi) 
{
	*xi = x;
	*yi = ys + (x - xs) * (ye - ys) / (xe - xs);
}

void horizontalIntersect(double xs, double ys, double xe, double ye, int y, double *xi, double *yi) 
{
	*yi = y;
	*xi = xs + (y - ys) * (xe - xs) / (ye - ys);
}

void clipLine(HDC hdc, int xs, int ys, int xe, int ye, int xleft, int xright, int ytop, int ybottom)
{
	double x1 = xs, x2 = xe, y1 = ys, y2 = ye;
	OutCode out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
	OutCode out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
	// we stop the loop if all = 0 (draw) or both have a common side (clip)
	while ((out1.All || out2.All) && !(out1.All & out2.All))
	{
		double xi, yi;
		if (out1.All)
		{
			if (out1.left)
				verticalIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
			else if (out1.right)
				verticalIntersect(x1, y1, x2, y2, xright, &xi, &yi);
			else if (out1.top)
				horizontalIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
			else 
				horizontalIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
			x1 = xi;
			y1 = yi;
			out1 = getOutCode(x1, y1, xleft, xright, ytop, ybottom);
		}
		else
		{
			if (out2.left)
				verticalIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
			else if (out2.right)
				verticalIntersect(x1, y1, x2, y2, xright, &xi, &yi);
			else if (out2.top)
				horizontalIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
			else 
				horizontalIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
			x2 = xi;
			y2 = yi;
			out2 = getOutCode(x2, y2, xleft, xright, ytop, ybottom);
		}
	}
	if (!out1.All && !out2.All)
		drawLineMethod1(hdc, x1, y1, x2, y2);
}

void clipPointToCircle(HDC hdc, int xs, int ys, int xc, int yc, int radius)
{
	int distance = sqrt((xs - xc)*(xs - xc) + (ys - yc)*(ys - yc));
	if (distance <= radius)
		SetPixel(hdc, xs, ys, RGB(0, 0, 0));
}

void clipLineToCircle(HDC hdc, int xa, int ya, int xb, int yb, double ccX, double ccY, double R) {
	int dx = xb - xa, dy = yb - ya, steps, k;
	float xIncrement, yIncrement, x = xa, y = ya;
	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	xIncrement = dx / (float)steps;
	yIncrement = dy / (float)steps;

	double rClipping;

	for (int k = 0; k < steps; k++) {
		rClipping = sqrt((x - ccX)*(x - ccX) + (y - ccY)*(y - ccY));
		if (rClipping < R) {
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
		x += xIncrement;
		y += yIncrement;

	}
}

int algo1 = 1, algo2 = 2, algo3 = 3, algo4 = 4, algo5 = 5, algo6 = 6, algo7 = 7, algo8 = 8, algo9 = 9, algo10 = 10, ch = -1;
int algo11 = 11, algo12 = 12, algo13 = 13, algo14 = 14, algo15 = 15, algo16 = 16, algo17 = 17, algo18 = 18, algo19 = 19;
int algo20 = 20, algo21 = 21;
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

		isFirstPress = 1;
		isSecondPress = 1;
		isThirdPress = 1;
	}break;
	case WM_LBUTTONDOWN: {
		if(isFirstPress)
		{
			hdc = GetDC(hWnd);

			x1 = LOWORD(lp);
			y1 = HIWORD(lp);

			if (ch == 18)
			{
				drawLineMethod1(hdc, Wleft, Wtop, Wright, Wtop);
				drawLineMethod1(hdc, Wleft, Wbottom, Wright, Wbottom);
				drawLineMethod1(hdc, Wleft, Wtop, Wleft, Wbottom);
				drawLineMethod1(hdc, Wright, Wtop, Wright, Wbottom);
				clipPoint(hdc, x1, y1, Wleft, Wright, Wtop, Wbottom);
			}
			else if (ch == 20)
			{
				drawCircleDirectCatesian(hdc, 450, 250, 150);
				clipPointToCircle(hdc, x1, y1, 450, 250, 150);
			}
			else
			{
				isFirstPress = 0;
				goto continueTakingInput1;
			}

			ReleaseDC(hWnd, hdc);
			isFirstPress = 1;continueTakingInput1:;
		}
		else if(isSecondPress)
		{
			hdc = GetDC(hWnd);

			x2 = LOWORD(lp);
			y2 = HIWORD(lp);

			if (ch == 5)
				drawLineDDA(hdc, x1, y1, x2, y2);
			else if (ch == 6)
				drawLineMethod1(hdc, x1, y1, x2, y2);
			else if (ch == 7)
				drawLineBresenham(hdc, x1, y1, x2, y2);
			else if (ch == 8)
				drawCircleDirectCatesian(hdc, x1, y1, sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			else if (ch == 9)
				drawCircleBasicPolar(hdc, x1, y1, sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			else if (ch == 10)
				drawCircleImprovedPolar(hdc, x1, y1, sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			else if (ch == 11)
				drawCircleBresenham(hdc, x1, y1, sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
			else if (ch == 12)
				drawFirstDegreeCurve(hdc, x1, y1, x2, y2);
			else if (ch == 19)
			{
				drawLineMethod1(hdc, Wleft, Wtop, Wright, Wtop);
				drawLineMethod1(hdc, Wleft, Wbottom, Wright, Wbottom);
				drawLineMethod1(hdc, Wleft, Wtop, Wleft, Wbottom);
				drawLineMethod1(hdc, Wright, Wtop, Wright, Wbottom);
				clipLine(hdc, x1, y1, x2, y2, Wleft, Wright, Wtop, Wbottom);
			}
			else if (ch == 21)
			{
				drawCircleDirectCatesian(hdc, 450, 250, 150);
				clipLineToCircle(hdc, x1, y1, x2, y2, 450, 250, 150);
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
				drawSecondDegreeCurve(hdc, x1, y1, s1x, s2y, x2, y2);
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
				drawHermiteCurve(hdc, x1, y1, s1x, s1y, x2, y2, s2x, s2y);
			else if(ch==15)
				drawBezierCurve(hdc, x1, y1, s1x, s1y, x2, y2, s2x, s2y);
			else if (ch == 16)
			{
				POINT points[4];
				points[0].x = x1;
				points[0].y = y1;
				points[1].x = s1x;
				points[1].y = s1y;
				points[2].x = x2;
				points[2].y = y2;
				points[3].x = s2x;
				points[3].y = s2y;
				drawSplines(hdc, points, 4, 0.06);
			}
			else if (ch == 17)
			{
				POINT points[4];
				points[0].x = x1;
				points[0].y = y1;
				points[1].x = s1x;
				points[1].y = s1y;
				points[2].x = x2;
				points[2].y = y2;
				points[3].x = s2x;
				points[3].y = s2y;
				convexFill(hdc, points, 4);
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