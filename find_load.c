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

//dtable 초기화
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
  (r,c)의 이웃이 (n_r, n_c)인데
  [1] 진짜 이웃인지 검사
  [2] 그 이웃까지 (r,c)를 거쳐가면 더 빠른지 검사
*/
void checkneighbor(int r, int c, int n_r, int n_c)
{
	//해당 좌표에 존재하지 않으면
	if (n_r < 0 && n_c < 0 && n_r >= sz && n_c >= sz)
	{
		return;
	}
	//벽이면
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
   (r,c) 위치의 이웃들에 대한 거리 정보 업데이트
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

	// 시작위치에 대해서 최단경로 확보!!!
	dtable[start_r][start_c].dist = 0;
	dtable[start_r][start_c].found = 1;

	// dijkstra 알고리즘 수행

	// (start_row, start_col)에서 갈 수 있는
	// vertex들에 대해서 업데이트
	updateNeighbor(start_r, start_c);

	// 지금까지 최단 경로가 결정되지 않은 vertex 중에서
	// 최소 거리를 가진 vertex를 선택
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
	// dtable에서 (start_row, start_col)
	// --> (end_row, end_col) 가는 경로를 지도에 표시

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