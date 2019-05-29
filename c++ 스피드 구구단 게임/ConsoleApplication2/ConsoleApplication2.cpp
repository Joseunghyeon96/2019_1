// ConsoleApplication2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <time.h>
#include <conio.h>
#include "SpeedGugudan.h"
using namespace std;


int main()
{
	srand((unsigned)time(NULL)); //rand함수 시드값생성

	int nPlay = 10; //테스트할 문제수
	printf("[스피드 구구단 게임!!]\n");
	printf("당신의 구구단 실력을 테스트 해보세요!!!\n");
	printf("%d번 테스트 하겠습니다.\n",nPlay);
	printf("크게 심호흡을 하시고...\n준비되면 엔터를 누르세요..");
	_getch(); // 키입력하면 게임시작
	system("cls");//콘솔화면 깨끗하게 지움

	double score = PlaySpeedGugu(nPlay); // 구구단 함수 실행후 score저장

	printf("\n점수 = %4.1f점(총%4.1f초)\n", score, playTime);
	//score변수명은 static으로 선언해서 메인에서도 사용가능
	//playtime은 static으로 선언하지 않아서 메인에서 불러올수 있음.
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
