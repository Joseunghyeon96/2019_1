#pragma once

class CMyTime
{
public:
	int hour;
	int minute;
	int second;
	CMyTime(int h, int m, int s);
	void print();
	void add(CMyTime);


};