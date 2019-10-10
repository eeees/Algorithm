/*
몇 queen을 할 것인지 입력받고
solution 개수를 출력한다.

*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int sz = 0;
int **chess_board;
int total_cnt = 0;
void initBoard()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			chess_board[i][j] = 0;
		}
	}
	return;
}

int isOK(int _r,int _c)
{
	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r][i] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			return 0;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (chess_board[i][j] != 0 && abs(_r - i) == abs(_c - j))
			{
				return 0;
			}
		}
	}

	return 1;
}

void clearChess(int _r)
{
	for (int i = 0; i < sz; i++)
	{
		chess_board[_r][i] = 0;
	}
	return;
}



void nextChess(int _r)
{
	for (int i = 0; i < sz; i++)
	{
		clearChess(_r);
		if (isOK(_r,i) == 1)
		{
			chess_board[_r][i] = 1;
			if (_r == sz - 1)
			{
				total_cnt++;
			}
			else
			{
				nextChess(_r + 1);
			}
		}
	}
}


int main(void)
{
	scanf("%d", &sz);
	chess_board = (int **)malloc(sizeof(int *)*sz);
	for (int i = 0; i < sz; i++)
	{
		chess_board[i] = (int *)malloc(sizeof(int)*sz);
	}

	for (int i = 0; i < sz; i++)
	{
		clearChess(0);

		if (isOK(0, i) == 1)
		{
			chess_board[0][i] = 1;
			nextChess(1);
		}
	}

	printf("%d\n", total_cnt);

	return 0;
}