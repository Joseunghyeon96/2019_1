#include <iostream>
#include "CStudent.h"

void CStudent::inputdata()
{
	cout << "이름을 입력하세요:" << endl;
	cin >> name;
	cout << "학번을 입력하세요:" << endl;
	cin >> ID;
	cout << "전공을 입력하세요:" << endl;
	cin >> major;
	cout << "학년을 입력하세요:" << endl;
	cin >> grade;

}

void CStudent::showdata()
{
	cout << "이름: " << name << "\t학번:" << ID << "\t전공:" << major << "\t학년:" << grade << endl;

}
