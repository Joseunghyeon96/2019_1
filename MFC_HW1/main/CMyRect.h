#pragma once

#include"CMyShape.h"

class CMyRect :public CMyShape
{
public:
	int w;
	int h;
	CMyRect();
	CMyRect(float fx, float fy, int iw, int ih);
	void draw();

};