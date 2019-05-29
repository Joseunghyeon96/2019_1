#include "SpeedGugudan.h"
using namespace std;

static int numGames = 0; // ���� Ƚ��
static int numWins = 0;//���� Ƚ��
static double score = 0;//����
double playTime = 0;//�÷���Ÿ�� 

// �÷���Ÿ���� ������ ���������� �� �ҽ� �ȿ����� �� ���̱⶧���� static���� ����

static bool checkAnswer() // �� �ҽ� �ȿ����� �� �Լ� -> static����
{
	int a = rand() % 8 + 2;
	int b = rand() % 8 + 2;
	int result;

	numGames++;
	printf("[%2d�� ����]:%2d x %2d = ", numGames, a, b);
	cin >> result;
	
	if (result == a * b)numWins++; // �����Ͻ� ���� Ƚ�� +1
	return (result == a * b);// �����Ͻ� true �� �����Ͻ� false�� ����
}


double PlaySpeedGugu(int nPlay)
{
	clock_t t0 = clock(); // ���ӽ��� �ð� ����
	for (int i = 0; i < nPlay; i++) //�׽�Ʈ Ƚ����ŭ ������ ���� ����
	{
		if (checkAnswer() == false) // checkAnswer �Լ� ������ ������ ���� ���
			printf("\t�����Դϴ�!\n");
	}
	clock_t t1 = clock(); // ���� ���� �� �ð� ����
	playTime = (double)(t1 - t0) / CLOCKS_PER_SEC; //�÷��� Ÿ�� ���

	//score = (numGames != numWins) ? 0.0 : 100 * (5.0 * numGames - playTime / (5.0 * numGames));
	// 1������ Ʋ���� 0�� �� ���� ��� ���� ���

	score = 100 * (5.0 * numWins - playTime / (5.0 * numGames));
	// �׳� ���

	return score; // score�� ����
}
