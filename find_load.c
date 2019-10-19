#include<stdio.h>

#define sz 5

struct dijkstra {
	int found;
	int dist;
	int prev_row;
	int prev_col;
};

struct coord {
	int row;
	int col;
};

struct dijkstra dtable[sz][sz];

char map[5][5] = {
	{'.','.','.','.','.'},
	{'.','#','#','#','.'},
	{'.','.','#','.','.'},
	{'.','#','#','.','#'},
	{'.','.','#','.','.'}
};

//dtable �ʱ�ȭ
void initDtalbe()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			dtable[i][j].dist = 99999;
			dtable[i][j].found = 0;
			dtable[i][j].prev_col = -1;
			dtable[i][j].prev_row = -1;
		}
	}
	return;
}

void dispMap()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			printf("%c ", map[i][j]);
		}
		printf("\n");
	}
	return;
}

/*
  (r,c)�� �̿��� (n_r, n_c)�ε�
  [1] ��¥ �̿����� �˻�
  [2] �� �̿����� (r,c)�� ���İ��� �� ������ �˻�
*/
void checkneighbor(int r, int c, int n_r, int n_c)
{
	//�ش� ��ǥ�� �������� ������
	if (n_r < 0 && n_c < 0 && n_r >= sz && n_c >= sz)
	{
		return;
	}
	//���̸�
	if (map[n_r][n_c] == '#')
	{
		return;
	}
	if (dtable[n_r][n_c].dist > dtable[r][c].dist + 1)
	{
		dtable[n_r][n_c].dist = dtable[r][c].dist + 1;
		dtable[n_r][n_c].prev_row = r;
		dtable[n_r][n_c].prev_col = c;
	}
	return;
}

/*
   (r,c) ��ġ�� �̿��鿡 ���� �Ÿ� ���� ������Ʈ
*/
void updateNeighbor(int r, int c)
{
	checkneighbor(r, c, r - 1, c);
	checkneighbor(r, c, r, c - 1);
	checkneighbor(r, c, r + 1, c);
	checkneighbor(r, c, r, c + 1);
	return;
}

struct coord findSmallest()
{
	int smallest_d = 999999;
	struct coord smallest;
	smallest.row = -1;
	smallest.col = -1;

	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			if (dtable[i][j].found == 0 &&
				dtable[i][j].dist < smallest_d)
			{
				smallest_d = dtable[i][j].dist;
				smallest.row = i;
				smallest.col = j;
			}
		}
	}
	return smallest;
}

int main(void)
{
	int start_r = 2;
	int start_c = 1;

	int end_r = 4;
	int end_c = 4;

	int tr, tc;

	initDtalbe();

	// ������ġ�� ���ؼ� �ִܰ�� Ȯ��!!!
	dtable[start_r][start_c].dist = 0;
	dtable[start_r][start_c].found = 1;

	// dijkstra �˰��� ����

	// (start_row, start_col)���� �� �� �ִ�
	// vertex�鿡 ���ؼ� ������Ʈ
	updateNeighbor(start_r, start_c);

	// ���ݱ��� �ִ� ��ΰ� �������� ���� vertex �߿���
	// �ּ� �Ÿ��� ���� vertex�� ����
	while (1)
	{
		struct coord smallest = findSmallest();
		if (smallest.row == -1 && smallest.col == -1)
		{
			break;
		}
		dtable[smallest.row][smallest.col].found = 1;
		updateNeighbor(smallest.row, smallest.col);
	}
	// dtable���� (start_row, start_col)
	// --> (end_row, end_col) ���� ��θ� ������ ǥ��

	tr = end_r;
	tc = end_c;

	while (1)
	{
		int temp_r;
		int temp_c;

		temp_r = dtable[tr][tc].prev_row;
		temp_c = dtable[tr][tc].prev_col;

		tr = temp_r;
		tc = temp_c;

		if (tr == -1 && tc == -1)
		{
			break;
		}
	}
	dispMap();
	return 0;
}