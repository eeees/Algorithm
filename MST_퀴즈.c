//MST
/*
<문제>
Undirected weighted graph가 주어졌을 때,

minimum spanning tree를 구성하는 edge들의 weight의 합을

구하시오.

그래프는 다음과 같이 주어진다.

N : vertex 개수 (vertex 번호는 0부터 시작, 연속번호)

V1 V2 W1: vertex v1과 vertex v2 사이에 weight W1 edge가 존재

...

-1 -1 -1 : edge의 입력 끝


입력
4

0 1 1

0 3 50

0 2 1

2 1 90

3 2 1

3 1 1

-1 -1 -1

출력
3
*/

//다음 퀴즈는 무조건 다 풀겠다!!!
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
//SLL에서 vertex 입력받아서 공간 할당 받는 법 공부하기☆

int vertex_num;
int edge_num;

struct node {
	int v;
	int weight;
	struct node *next;
};

struct edge {
	int src;
	int dst;
	int weight;
};

struct node *graph = 0;
struct edge *edges=0;

int *cycle_d;

void sameGroup(int v1, int v2)
{
	int g1 = cycle_d[v1];
	int g2 = cycle_d[v2];
	int smaller, bigger = 0;

	if (g1 > g2)
	{
		bigger = g1;
		smaller = g2;
	}
	else
	{
		bigger = g2;
		smaller = g1;
	}

	for (int i = 0; i < vertex_num; i++)
	{
		if (cycle_d[i] == bigger)
		{
			cycle_d[i] = smaller;
		}
	}
	return;
}

void swap(int e1, int e2)
{
	struct edge temp;
	temp = edges[e1];
	edges[e1] = edges[e2];
	edges[e2] = temp;
	return;
}

void addEdge(int v1, int v2, int w, int doreverse)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v2;
	new_one->next = 0;
	new_one->weight = w;


	if (graph[v1].v == 0)
	{
		graph[v1].v = v1;
		graph[v1].weight = w;

	}
	if (graph[v1].next == 0)
	{
		graph[v1].next = new_one;
	}
	else
	{
		struct node *temp = graph[v1].next;


		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;

	}
	if (doreverse == 1)
	{
		addEdge(v2, v1, w, 0);
	}
	//printf("%d %d\n", graph[0].next->v, graph[0].weight);
	return;
}


void sortEdge()
{
	int edge_idx = 0;
	for (int i = 0; i < vertex_num; i++)
	{
		struct node *cur = graph[i].next;
		while (cur != 0)
		{
			edges[edge_idx].src = i;
			edges[edge_idx].dst = cur->v;
			edges[edge_idx].weight = cur->weight;
			edge_idx++;
			cur = cur->next;
		}
	}
	int x, y;
	for (y = 0; y < edge_num; y++)
	{
		for (x = 0; x < edge_num - 1 - y; x++)
		{
			if (edges[x].weight > edges[x + 1].weight)
			{
				swap(x, x + 1);
			}
		}
	}
	return;
}

int doMST()
{
	int weight_cnt = 0;
	int edge_cnt = 0;
	for (int i = 0; i < edge_num; i++)
	{
		if (cycle_d[edges[i].src] != cycle_d[edges[i].dst])
		{
			//printf("%d----%d(%d)\n", edges[i].src, edges[i].dst, edges[i].weight);
			weight_cnt = weight_cnt + edges[i].weight;
			edge_cnt++;
			if (edge_cnt == vertex_num - 1)
			{
				return weight_cnt;
			}
			sameGroup(edges[i].src, edges[i].dst);
		}
	}
}

int main(void)
{

	scanf("%d", &vertex_num);


	graph = (struct node *)malloc(sizeof(struct node)*vertex_num);
	//초기화
	for (int i = 0; i < vertex_num; i++)
	{
		graph[i].v = 0;
		graph[i].next = 0;
		graph[i].weight = 0;
	}
	cycle_d = (int *)malloc(sizeof(int)*vertex_num);
	for (int i = 0; i < vertex_num; i++)
	{
		cycle_d[i] = i;
	}

	int v1, v2, w;
	while (1)
	{

		scanf("%d %d %d", &v1, &v2, &w);
		if (v1 == -1 && v2 == -1 && w == -1)
		{
			break;
		}
		
		addEdge(v1, v2, w, 0);
		edge_num++;
	}

	edges = (struct edge*)malloc(sizeof(struct edge)*edge_num);
	for (int i = 0; i < edge_num; i++)
	{
		edges[i].src = 0;
		edges[i].dst = 0;
		edges[i].weight = 0;
	}

	//printf("edges의 개수는 : %d\n", edge_num);

	sortEdge();
	int cnt=doMST();
	printf("%d\n", cnt);

	/*
	//printf("edge 저장 끝\n");
	struct node *temp = graph[0].next;
	//printf("vertex 출력\n");
	//printf("%d %d\n", graph[0].v, graph[0].weight);
	while (temp != 0)
	{
		printf("%d %d\n", temp->v, temp->weight);
		temp = temp->next;
	}
	*/
	return 0;
}
