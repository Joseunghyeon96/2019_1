#pragma once
#include <string>
using namespace std;

class CStudent {

public:
	string name ;
	string ID;
	string major;
	string grade;//�г��� 1�̳� 2���� ���ڰ��ƴ� 1�г�, 2�г����ε� ���� �ְԲ� string���

	void inputdata();
	void showdata();


};