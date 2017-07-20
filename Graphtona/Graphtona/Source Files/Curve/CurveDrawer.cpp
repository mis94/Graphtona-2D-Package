#include "..\..\Header Files\Curve\CurveDrawer.h"

int CurveDrawer::mulitplyTwoVectors(int v1[], int v2[], int size)
{
	int ret = 0;
	for (int i = 0;i < size;i++)
		ret += v1[i] * v2[i];
	return ret;
}