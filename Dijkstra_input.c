/*
5
0 1 1
0 2 3
0 4 5
1 2 2
1 4 4
2 4 6
2 3 7
3 4 8
-1 -1 -1
*/

#include<stdio.h>
#include<stdlib.h>

struct node {
	//char name;
	int v;
	int weight;
	struct node *next;
};

struct dijkstra {
	int found;
	int distance;
	int prev;
};

struct node *graph = 0;
struct dijkstra *dtable = 0;

int vertex_num;

void initDtable()
{
	for (int i = 0; i < vertex_num; i++)
	{
		dtable[i].distance = 99999;
		dtable[i].found = 0;
		dtable[i].prev = -1;
	}
	return;
}

void addEdge(int v1, int v2, int w, int doreverse)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v2;
	new_one->weight = w;
	new_one->next = 0;


	if (graph[v1].next == 0)
	{
		graph[v1].next = new_one;
	}
	else
	{
		struct node *cur = graph[v1].next;
		if (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new_one;
	}
	if (doreverse == 1)
	{
		addEdge(v2, v1, w, 0);
	}
	return;
}

int NextVertex()
{
	//distance가 가장 작은 것 찾기
	int smaller_d = 99999;
	int smaller_v = -1;

	for (int i = 0; i < vertex_num; i++)
	{
		if (dtable[i].found == 0 && dtable[i].distance < smaller_d)
		{
			smaller_d = dtable[i].distance;
			smaller_v = i;
		}
	}
	return smaller_v;
}

void update_d(int v)
{
	struct node *cur = graph[v].next;
	while (cur != 0)
	{
		if (dtable[cur->v].found == 0 && dtable[cur->v].distance > dtable[v].distance + cur->weight)
		{
			dtable[cur->v].distance = dtable[v].distance + cur->weight;
			dtable[cur->v].prev = v;
		}
		cur = cur->next;
	}
	return;
}


void show_d()
{
	printf("\n");
	for (int i = 0; i < vertex_num; i++)
	{
		printf("%d: %d %d %d\n", i, dtable[i].found, dtable[i].distance, dtable[i].prev);
	}
	return;
}
void doDijkstra(int v)
{
	//v와 가까운 경로를 찾기
	dtable[v].distance = 0;

	int next_v = 0;
	while ((next_v = NextVertex()) != -1)
	{
		dtable[next_v].found = 1;
		update_d(next_v);
	}
	show_d();
	return;
}



int main(void)
{
	scanf("%d", &vertex_num);
	printf("vertex의 개수는 %d\n", vertex_num);
	graph = (struct node *)malloc(sizeof(struct node)*vertex_num);
	dtable = (struct dijkstra*)malloc(sizeof(struct dijkstra)*vertex_num);

	for (int i = 0; i < vertex_num; i++)
	{
		graph[i].v = 0;
		graph[i].weight = 0;
		graph[i].next = 0;
	}

	int v1, v2, w;

	while (1)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		if (v1 == -1 && v2 == -1 && w == -1)
		{
			break;
		}
		//printf("%d %d %d\n", v1, v2, w);
		addEdge(v1, v2, w, 1);
	}


	initDtable();
	doDijkstra(0);

	return 0;
}
