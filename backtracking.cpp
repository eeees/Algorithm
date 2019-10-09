//backtracking
//8 Queens

//�밢���� �־ �ȵǰ� �����¿쿡�� ������ �ȵȴ�.

#include<stdio.h>
#include<string.h>
#include<math.h>

//������ ũ�� �Է¹޴°� �ѹ� �غ���
#define sz 4
int chess_board[sz][sz];

int solutionCnt = 0;


void initBoard()
{
	memset(chess_board, 0, sizeof(int)*sz*sz);

#if 0
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			chess_board[i][j] = 0;
		}
	}
#endif
	return;
}

//�ش� ��ҿ� queen�� ���Ƶ� �Ǵ°�
int isOK(int _r, int _c)//���
{
	//chess board�� 0�̸� �����.
	//����, ����, ���� �밢���� queen�� �ִ��� �ľ��ϸ� �ȴ�.
	//�ֳ��ϸ� �Ʒ��ʰ� ������, ���� �밢���� queen�� �ϳ��� ���⶧��.(�˻縦 ���� ����)

	//���� ���� �˻�
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			//queen�� �����Ѵ�.
			return 0;
		}
	}

	//���� ���� �˻�
	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r][i])
		{
			return 0;
		}
	}
	//���� �밢�� ���� �˻�
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (abs(i - _r) == abs(j - _c) && chess_board[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}


void clearRow(int _r)
{
	//memset(&chess_board[_r][0],0,sizeof(int*)*sz);
	for (int i = 0; i < sz; i++)
	{
		chess_board[_r][i] = 0;
	}
}


void printfSolution()
{
	solutionCnt++;
	printf("---------Solution %d---------\n", solutionCnt);
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			printf("%d ", chess_board[i][j]);
		}
		printf("\n");
	}
	return;
}


//�� _r�� queen�� ���� �� �ִ� ��ġ�� ã�´�.
void checkNext(int _r)
{
	//�� _r�� ��� ���� ����
	for (int i = 0; i < sz; i++)
	{
		//������ �˻��ߴ� 1 �����
		clearRow(_r);

		if (isOK(_r, i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == (sz - 1))
			{
				printfSolution();
			}
			else
			{
				checkNext(_r + 1);
			}
		}
	}
}


int main(void)
{
	int c; //���� ��Ÿ���� ����

	initBoard();

	for (c = 0; c < sz; c++)
	{
		clearRow(0);
		if (isOK(0, c) == 1)
		{
			chess_board[0][c] = 1;
			checkNext(1);
		}
	}
	return 0;
}