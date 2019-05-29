// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
using namespace std;

int* SearchRecPoint(int* arr[])
{
	int* resultPoint = new int[2]{ 0,0 };
	int exceptCheck = 0;


	if (arr[0][0] == arr[1][0])
		exceptCheck++;
	if (arr[0][0] == arr[2][0])
		exceptCheck++;
	if (arr[1][0] == arr[2][0])
		exceptCheck++;
	if (arr[0][1] == arr[1][1])
		exceptCheck++;
	if (arr[0][1] == arr[2][1])
		exceptCheck++;
	if (arr[1][1] == arr[2][1])
		exceptCheck++;

	if (exceptCheck != 2)
	{
		printf("정사각형 또는 직사각형의 모양이 아닙니다.\n");
		return resultPoint;
	}



	if (arr[0][0] == arr[1][0])
		resultPoint[0] = arr[2][0];
	if (arr[0][0] == arr[2][0])
		resultPoint[0] = arr[1][0];
	if (arr[1][0] == arr[2][0])
		resultPoint[0] = arr[0][0];

	if (arr[0][1] == arr[1][1])
		resultPoint[1] = arr[2][1];
	if (arr[0][1] == arr[2][1])
		resultPoint[1] = arr[1][1];
	if (arr[1][1] == arr[2][1])
		resultPoint[1] = arr[0][1];


	return resultPoint;
}
int main()
{
	int* test[3];

	int* result;

	test[0] = new int[2]{ 2,7 };
	test[1] = new int[2]{ 3,3 };
	test[2] = new int[2]{ 4,7 };

	result = SearchRecPoint(test);

	cout << result[0] << "," << result[1] << endl; // 1,7

	delete[] test[0];
	delete[] test[1];
	delete[] test[2];
	delete result;
	system("pause");
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
