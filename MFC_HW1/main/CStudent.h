#pragma once
#include <string>
using namespace std;

class CStudent {

public:
	string name ;
	string ID;
	string major;
	string grade;//학년을 1이나 2같은 숫자가아닌 1학년, 2학년으로도 쓸수 있게끔 string사용

	void inputdata();
	void showdata();


};