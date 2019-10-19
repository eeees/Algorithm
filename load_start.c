#include<stdio.h>
#include<stdlib.h>

//sz 입력받고 시작,끝 입력받기
//길에 '*'이 있으면 cnt하기
int sz;
int cnt = 0;
char **map;
struct dijkstra {
	int found;
	int dist;
	int prev_r;
	int prev_c;
};

struct coord {
	int row;
	int col;
};

struct dijkstra **dtable=0;

void initDtable()
{
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			dtable[i][j].dist = 999999;
			dtable[i][j].found = 0;
			dtable[i][j].prev_c = -1;
			dtable[i][j].prev_r = -1;
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
}

//주변 이웃이 맞는지
void checkNeighbor(int r, int c, int n_r, int n_c)
{
	if (n_r < 0 || n_c < 0 || n_r >= sz || n_c >= sz)
	{
		return;
	}
	if (map[n_r][n_c] == '#') //문제!
	{
		return;
	}
	if (dtable[n_r][n_c].dist > dtable[r][c].dist + 1)
	{
		dtable[n_r][n_c].dist = dtable[r][c].dist + 1;
		dtable[n_r][n_c].prev_c = c;
		dtable[n_r][n_c].prev_r = r;
	}
	return;
}

void updateNeighbor(int r, int c)
{
	checkNeighbor(r, c, r + 1, c);
	checkNeighbor(r, c, r - 1, c);
	checkNeighbor(r, c, r, c - 1);
	checkNeighbor(r, c, r, c + 1);
	return;
}

struct coord findSmall()
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

void doDijkstra(int r, int c)
{
	//dijkstra
	int tr;
	int tc;
	struct coord next;
	updateNeighbor(r, c);
	while (1)
	{
		next = findSmall();
		if (next.row == -1 && next.col == -1)
		{
			return;
		}
		dtable[next.row][next.col].found = 1;
		updateNeighbor(next.row, next.col);
	}
	return;
}

void checkload(int e_r, int e_c)
{
	int tr;
	int tc;

	tr = e_r;
	tc = e_c;

	while (1)
	{
		int temp_r;
		int temp_c;
		//보석이다!
		if (map[tr][tc] == '*')
		{
			cnt++;
		}
		map[tr][tc] = '$';
		temp_r = dtable[tr][tc].prev_r;
		temp_c = dtable[tr][tc].prev_c;

		tr = temp_r;
		tc = temp_c;
		if (tr == -1 && tc == -1)
		{
			break;
		}
	}
	dispMap();
}

int main(void)
{
	printf("sz를 입력하시오 : ");
	scanf("%d", &sz);
	int start_r;
	int start_c;
	printf("시작 지점을 입력하시오 : ");
	scanf("%d %d", &start_r, &start_c);
	int end_r;
	int end_c;
	printf("도착 지점을 입력하시오 : ");
	scanf("%d %d", &end_r, &end_c);

	dtable = (struct dijkstra **)malloc(sizeof(struct dijkstra)*sz);
	for (int i = 0; i < sz; i++)
	{
		dtable[i] = (struct dijkstra *)malloc(sizeof(struct dijkstra)*sz);
	}
	map = (char **)malloc(sizeof(char )*sz);
	for (int i = 0; i < sz; i++)
	{
		map[i] = (char *)malloc(sizeof(char)*sz);
	}
	//map input
	printf("map input start!\n");
	char string;
	for (int i = 0; i < sz; i++)
	{
		for (int j = 0; j < sz; j++)
		{
			scanf("%c", &string);
			if (string != '\n')
			{
				map[i][j] = string;
			}
			else
			{
				scanf("%c", &string);
				map[i][j] = string;
			}
		}
	}
	


	initDtable();
	//dispMap();
	//printf("%c\n", map[0][0]);
	//printf("%c\n", map[0][1]);

#if 1
	dtable[start_r][start_c].dist = 0;
	dtable[start_r][start_c].found = 1;

	//dijkstra
	doDijkstra(start_r, start_c);

	checkload(end_r, end_c);

	printf("\n");
	printf("보석의 개수는 : %d\n", cnt);
#endif
	return 0;
}