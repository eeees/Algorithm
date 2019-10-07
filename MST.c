#include<stdio.h>
#include<stdlib.h>

#define vertex_num 5
#define edges_num 8

struct node {
	int v;
	int weight;
	struct node *next;
};

struct node *graph[vertex_num];
struct edge {
	int src;
	int dst;
	int weight;
};

struct edge edges[edges_num];

//같은 소속인지
//초기화 잊지말기
int cycle_detection[vertex_num] = { 0,1,2,3,4 };

void addEdge(int v1, int v2, int w)
{
	struct node *new_one = (struct node*)malloc(sizeof(struct node));
	new_one->v = v2;
	new_one->weight = w;
	new_one->next = 0;

	struct node *cur = graph[v1];
	if (cur == 0)
	{
		graph[v1] = new_one;
		return;
	}
	else
	{
		while (cur->next != 0)
		{
			cur = cur->next;
		}
		cur->next = new_one;
	}
	return;
}

void sameGroup(int e1, int e2)
{
	//해당 edge의 weight를 비교해서 작은 것으로 통일시키기위해
	int g1 = cycle_detection[e1];
	int g2 = cycle_detection[e2];
	int smaller, bigger;

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
		if (cycle_detection[i] == bigger)
		{
			cycle_detection[i] = smaller;
		}
	}
	return;
}
void swap(int v1, int v2)
{
	//edge sort할 때 필요
	struct edge temp;
	temp = edges[v1];
	edges[v1] = edges[v2];
	edges[v2] = temp;

	return;
}

void sortEdge()
{
	/*
	1. 모든 edge를 edges 배열에 넣기
	2. bubble sort를 통해 오름차순으로 정렬
	*/

	int edge_idx = 0;

	for (int i = 0; i < vertex_num; i++)
	{
		struct node *cur = graph[i];
		while (cur != 0)
		{
			edges[edge_idx].src = i;
			edges[edge_idx].dst = cur->v;
			edges[edge_idx].weight = cur->weight;
			edge_idx++;
			cur = cur->next;
		}
	}

	for (int i = 0; i < edges_num; i++)
	{
		for (int x = 0; x < edges_num - i-1; x++)
		{
			if (edges[x].weight > edges[x + 1].weight)
			{
				swap(x,x+1);
			}
		}
	}

}

void doMST()
{
	int edge_cnt = 0;
	for (int i = 0; i < edges_num; i++)
	{
		if (cycle_detection[edges[i].src] != cycle_detection[edges[i].dst])
		{
			printf("%d----%d(%d)\n", edges[i].src, edges[i].dst, edges[i].weight);
			edge_cnt++;
			if (edge_cnt ==vertex_num-1)
			{
				return;
			}
			sameGroup(edges[i].src, edges[i].dst);

		}
	}
}




int main(void)
{

	addEdge(0, 1, 1);
	addEdge(0, 2, 3);
	addEdge(0, 4, 5);
	addEdge(1, 2, 2);
	addEdge(1, 4, 4);
	addEdge(2, 4, 6);
	addEdge(2, 3, 7);
	addEdge(3, 4, 8);

	sortEdge();

	doMST();

	return 0;
}