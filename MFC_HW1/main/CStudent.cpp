#include <iostream>
#include "CStudent.h"

void CStudent::inputdata()
{
	cout << "�̸��� �Է��ϼ���:" << endl;
	cin >> name;
	cout << "�й��� �Է��ϼ���:" << endl;
	cin >> ID;
	cout << "������ �Է��ϼ���:" << endl;
	cin >> major;
	cout << "�г��� �Է��ϼ���:" << endl;
	cin >> grade;

}

void CStudent::showdata()
{
	cout << "�̸�: " << name << "\t�й�:" << ID << "\t����:" << major << "\t�г�:" << grade << endl;

}
