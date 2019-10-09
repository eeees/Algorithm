//backtracking
//8 Queens

//대각선에 있어도 안되고 상하좌우에도 있으면 안된다.

#include<stdio.h>
#include<string.h>
#include<math.h>

//무조건 크기 입력받는건 한번 해보기
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

//해당 장소에 queen을 놓아도 되는가
int isOK(int _r, int _c)//행렬
{
	//chess board가 0이면 비었다.
	//위쪽, 왼쪽, 위의 대각선만 queen이 있는지 파악하면 된다.
	//왜냐하면 아래쪽과 오른쪽, 밑의 대각선은 queen이 하나도 없기때문.(검사를 아직 안함)

	//위쪽 방향 검사
	for (int i = 0; i < _r; i++)
	{
		if (chess_board[i][_c] != 0)
		{
			//queen이 존재한다.
			return 0;
		}
	}

	//왼쪽 방향 검사
	for (int i = 0; i < _c; i++)
	{
		if (chess_board[_r][i])
		{
			return 0;
		}
	}
	//위쪽 대각선 방향 검사
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


//행 _r에 queen을 놓을 수 있는 위치를 찾는다.
void checkNext(int _r)
{
	//행 _r의 모든 열에 대해
	for (int i = 0; i < sz; i++)
	{
		//이전에 검사했던 1 지우기
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
	int c; //열을 나타내는 변수

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