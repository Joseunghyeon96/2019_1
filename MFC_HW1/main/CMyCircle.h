#pragma once
#include"CMyShape.h"

class  CMyCircle :public CMyShape
{
public:
	float r;
	CMyCircle();
	CMyCircle(float fx, float fy, float ir);
	void draw();
};