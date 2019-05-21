#include<iostream>
#include"CMyRect.h"
using namespace std;

CMyRect::CMyRect():CMyShape()
{
	w = 0;
	h = 0;
}

CMyRect::CMyRect(float fx, float fy, int iw, int ih):CMyShape(fx,fy)
{
	w = iw;
	h = ih;
}

void CMyRect::draw()
{
	cout << "[MyRect](" << m_x << "," << m_y << ") w:" << w << " h: " << h << endl;

}
