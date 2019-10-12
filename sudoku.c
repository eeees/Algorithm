/*
1. region 안에 1~9까지 한번씩만 들어가야함
2.가로, 세로에서도 1~9까지 한번씩만 들어가야함.
*/

#include<stdio.h>
#include<string.h>

#define sz 9 //9*9

void solvesudoku(int _r, int _c);

//sudoku board
int sudoku[sz][sz] = {
	4, 0, 7, 5, 0, 0, 0, 0, 8,
	0, 5, 0, 7, 0, 0, 4, 0, 9,
	0, 0, 6, 0, 0, 4, 0, 7, 0,
	9, 0, 0, 6, 0, 0, 2, 4 ,3,
	0, 4, 0, 9, 0, 3, 0, 8, 0,
	7, 3, 1, 0, 0, 2, 0, 0, 5,
	0, 2, 0, 8, 0, 0, 7, 0, 0,
	3, 0, 9, 0, 0, 6, 0, 5, 0,
	5, 0, 0, 0, 0, 7, 3, 0, 4
};

//처음에 주어진 sudoku(초기화)
int readOnlySudoku[sz][sz];

//해답의 개수
int solutionCnt = 0;

//readOnlySudoku 배열에 주어진 sudoku를 저장한다.
void initReadOnlySudoku()
{
	//목적지, 출발지, 크기
	memcpy(readOnlySudoku, sudoku, sz*sz * sizeof(int));

}

//좌표(_r, _c)에 값 _value가 들어갈 수 있는 지 확인
//반환값이 1이면 가능하다.'
int isOK(int _r, int _c, int _value)
{
	//상하
	for (int i = 0; i < sz; i++)
	{
		//이미 _value값을 가진 곳이 있다.
		if (sudoku[i][_c] == _value && i != _r)
		{
			return 0;
		}
	}
	//좌우
	for (int i = 0; i < sz; i++)
	{
		if (sudoku[_r][i] == _value && i != _c)
		{
			return 0;
		}
	}

	//region
	//3으로 나눈 후, 다시 3을 곱한다.
	int region_row = _r / 3;
	int region_col = _c / 3;

	for (int i = region_row * 3; i <= region_row * 3 + 2; i++)
	{
		for (int j = region_col * 3; j <= region_col * 3 + 2; j++)
		{
			if (sudoku[i][j] == _value && i != _r && j != _c)
			{
				return 0;
			}
		}
	}

	//(_r,_c)에 _value값을 넣어도 된다.
	return 1;
}


void printSolution()
{
	solutionCnt++;

	printf("-----Solution # %d-----\n", solutionCnt);

	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			printf("%d  ", sudoku[i][j]);
		}
		printf("\n");
	}
	return;
}

//좌표(_r,_c) 다음에 방문하여 숫자를 결정할 위치 판단
void chectNext(int _r, int _c)
{
	if (_r == sz - 1 && _c == (sz - 1))
	{
		printSolution();
		return;
	}
	_c++;
	if (_c == sz)
	{
		_c = 0;
		_r++;
	}
	solvesudoku(_r, _c);
}


//좌표 (_r, _c) 위치에 들어갈 숫자를 결정한다.
void solvesudoku(int _r, int _c)
{
	//이미 숫자가 주어져 있을 때,
	if (sudoku[_r][_c] > 0)
	{
		//다음 칸으로 이동
		chectNext(_r, _c);
	}
	else
	{
		//좌표(_r, _c)에 1부터 9까지 숫자를 하나씩 대입하여 체크
		for (int i = 1; i <= 9; i++)
		{
			//clear
			memcpy(&sudoku[_r][_c], &readOnlySudoku[_r][_c], sizeof(int)*sz*sz - sizeof(int)*(_r*sz + _c));
			if (isOK(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				//다음 칸으로 이동해서 처리
				chectNext(_r, _c);
			}
		}
	}
	return;
}



int main(void)
{
	//복사본 생성
	initReadOnlySudoku();

	//맨 윗줄부터 찾는다.
	solvesudoku(0, 0);


	return 0;
}