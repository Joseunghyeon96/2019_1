#include <iostream>
#include "CMyTime.h"
using namespace std;

CMyTime::CMyTime(int h,int m,int s)
{
	hour = h;
	minute = m;
	second = s;

	if (second >= 60)
	{
		minute += second / 60;
		second = second % 60;
	}

	if (minute >= 60)
	{
		hour += minute / 60;
		minute = minute % 60;
	}
}

void CMyTime::print()
{
	printf("%02d:%02d:%02d\n", hour, minute, second);
}

void CMyTime::add(CMyTime a)
{
	hour += a.hour;
	minute += a.minute;
	second += a.second;

	if (second >= 60)
	{
		minute += second / 60;
		second = second % 60;
	}

	if (minute >= 60)
	{
		hour += minute / 60;
		minute = minute % 60;
	}
}
