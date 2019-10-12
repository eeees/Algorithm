/*
1. region �ȿ� 1~9���� �ѹ����� ������
2.����, ���ο����� 1~9���� �ѹ����� ������.
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

//ó���� �־��� sudoku(�ʱ�ȭ)
int readOnlySudoku[sz][sz];

//�ش��� ����
int solutionCnt = 0;

//readOnlySudoku �迭�� �־��� sudoku�� �����Ѵ�.
void initReadOnlySudoku()
{
	//������, �����, ũ��
	memcpy(readOnlySudoku, sudoku, sz*sz * sizeof(int));

}

//��ǥ(_r, _c)�� �� _value�� �� �� �ִ� �� Ȯ��
//��ȯ���� 1�̸� �����ϴ�.'
int isOK(int _r, int _c, int _value)
{
	//����
	for (int i = 0; i < sz; i++)
	{
		//�̹� _value���� ���� ���� �ִ�.
		if (sudoku[i][_c] == _value && i != _r)
		{
			return 0;
		}
	}
	//�¿�
	for (int i = 0; i < sz; i++)
	{
		if (sudoku[_r][i] == _value && i != _c)
		{
			return 0;
		}
	}

	//region
	//3���� ���� ��, �ٽ� 3�� ���Ѵ�.
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

	//(_r,_c)�� _value���� �־ �ȴ�.
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

//��ǥ(_r,_c) ������ �湮�Ͽ� ���ڸ� ������ ��ġ �Ǵ�
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


//��ǥ (_r, _c) ��ġ�� �� ���ڸ� �����Ѵ�.
void solvesudoku(int _r, int _c)
{
	//�̹� ���ڰ� �־��� ���� ��,
	if (sudoku[_r][_c] > 0)
	{
		//���� ĭ���� �̵�
		chectNext(_r, _c);
	}
	else
	{
		//��ǥ(_r, _c)�� 1���� 9���� ���ڸ� �ϳ��� �����Ͽ� üũ
		for (int i = 1; i <= 9; i++)
		{
			//clear
			memcpy(&sudoku[_r][_c], &readOnlySudoku[_r][_c], sizeof(int)*sz*sz - sizeof(int)*(_r*sz + _c));
			if (isOK(_r, _c, i) == 1)
			{
				sudoku[_r][_c] = i;
				//���� ĭ���� �̵��ؼ� ó��
				chectNext(_r, _c);
			}
		}
	}
	return;
}



int main(void)
{
	//���纻 ����
	initReadOnlySudoku();

	//�� ���ٺ��� ã�´�.
	solvesudoku(0, 0);


	return 0;
}