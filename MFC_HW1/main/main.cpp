// main.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "CStudent.h"
#include "CMyTime.h"
#include <iostream>
#include"CMyCircle.h"
#include"CMyRect.h"
#include"CMyShape.h"

int main()
{
	int num=0;
	CStudent students[3];
	CMyTime a(0, 70, 90);
	CMyTime b(0, 0, 3630);


	while(true){
		cout << "어떤 기능을 사용하고 싶으십니까? (종료:4)" << endl;
		cin >> num;

		CMyShape * pShape1 = new CMyShape(10.0, 3.5);
		CMyShape * pShape2 = new CMyRect(3.0, 5.5, 7, 8);
		CMyShape * pShape3 = new CMyCircle(4.5, 5.5, 1.0);//CMyShape클래스 변수를 반복문 밖에 놓으면 case3마지막에 delete때문에 2번 실행은 안되기 때문에
		                                                  //반복문 안쪽에 위치 시켰습니다.
		
		switch (num) {

		case 1:
		
			for (int i = 0; i < 3; i++)
				students[i].inputdata();
			for (int i = 0; i < 3; i++)
				students[i].showdata();
			break;

		case 2:

			a.print();
			b.print();

			a.add(b);
			a.print();
			break;
		case 3:

			pShape1->draw();
			pShape2->draw();
			pShape3->draw();
			delete pShape1;
			delete pShape2;
			delete pShape3;
			
			break;

		case 4:
			return 0;
		}
	
	}
	return 0;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
