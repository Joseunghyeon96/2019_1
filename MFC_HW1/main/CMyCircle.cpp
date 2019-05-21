#include<iostream>
#include"CMyCircle.h"
using namespace std;

CMyCircle::CMyCircle() :CMyShape()
{
	r = 0;

}

CMyCircle::CMyCircle(float fx, float fy,float ir) :CMyShape(fx, fy)
{
	r = ir;

}

void CMyCircle::draw()
{
	cout << "[MyCircle](" << m_x << "," << m_y << ")" << " r:" << r << endl;

}