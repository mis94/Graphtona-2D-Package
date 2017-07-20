#include "..\..\Header Files\Filling\EdgeRecord.h"

EdgeRecord::EdgeRecord()
{
	xLeft = INT_MAX;
	xRight = INT_MIN;
}

EdgeRecord::EdgeRecord(int xLeft, int xRight)
{
	EdgeRecord::xLeft = xLeft;
	EdgeRecord::xRight = xRight;
}