#include "SpeedGugudan.h"
using namespace std;

static int numGames = 0; // 문제 횟수
static int numWins = 0;//맞힌 횟수
static double score = 0;//점수
double playTime = 0;//플레이타임 

// 플레이타임을 제외한 전역변수는 이 소스 안에서만 쓸 것이기때문에 static으로 선언

static bool checkAnswer() // 이 소스 안에서만 쓸 함수 -> static선언
{
	int a = rand() % 8 + 2;
	int b = rand() % 8 + 2;
	int result;

	numGames++;
	printf("[%2d번 문제]:%2d x %2d = ", numGames, a, b);
	cin >> result;
	
	if (result == a * b)numWins++; // 정답일시 맞힌 횟수 +1
	return (result == a * b);// 정답일시 true 값 오답일시 false값 리턴
}


double PlaySpeedGugu(int nPlay)
{
	clock_t t0 = clock(); // 게임시작 시간 저장
	for (int i = 0; i < nPlay; i++) //테스트 횟수만큼 구구단 문제 실행
	{
		if (checkAnswer() == false) // checkAnswer 함수 실행후 오답이 나올 경우
			printf("\t오답입니다!\n");
	}
	clock_t t1 = clock(); // 게임 종료 후 시간 저장
	playTime = (double)(t1 - t0) / CLOCKS_PER_SEC; //플레이 타임 계산

	//score = (numGames != numWins) ? 0.0 : 100 * (5.0 * numGames - playTime / (5.0 * numGames));
	// 1문제라도 틀리면 0점 다 맞을 경우 점수 계산

	score = 100 * (5.0 * numWins - playTime / (5.0 * numGames));
	// 그냥 계산

	return score; // score값 리턴
}
