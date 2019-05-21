#include<iostream>
#include"CMyShape.h"
using namespace std;

CMyShape::CMyShape()
{
	m_x = 0;
	m_y = 0;


}

CMyShape::CMyShape(float fx, float fy)
{
	m_x = fx;
	m_y = fy;

}

void CMyShape::draw()
{
	cout << fixed;
	cout.precision(1);//구글링했습니다.
	cout << "[MyShape](" << m_x << "," << m_y << ")" << endl;

}