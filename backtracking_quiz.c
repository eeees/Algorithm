#include<stdio.h>
#include<stdio.h>
#define sz 8

int board[sz][sz];
int cnt = 0;

struct num {
	int num;
	int x;
	int y;
};

struct num edge[100];

void init()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			board[i][j] = 0;
		}
	}
}

void clear(int _r)
{
	for (int i = 0; i < _r; i++)
	{
		board[_r][i] = 0;
	}
	return;
}
void isOK(int _r, int _c)
{
	for (int i = 0; i < _c; i++)
	{
		if (board[_r][i] != 0)
		{
			cnt++;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		if (board[i][_c] != 0)
		{
			cnt++;
		}
	}
	for (int i = 0; i < _r; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (board[i][j] != 0 && abs(i - _r) == abs(j - _c))
			{
				cnt++;
			}
		}
	}
	return;
}


int main(void)
{
	init();
	int num1;

	int x1;
	int y1;
	int c = 0;
	while (1)
	{
		scanf("%d %d %d", &num1, &x1, &y1);
		if (num1 == -1 && x1 == -1 && y1 == -1)
		{
			break;
		}
		board[x1][y1] = 1;
		edge[num1].x = x1;
		edge[num1].y = y1;
	}
	int a;
	scanf("%d", &a);
	isOK(edge[a].x, edge[a].y);

	printf("%d\n", cnt);
	
	return 0;
}