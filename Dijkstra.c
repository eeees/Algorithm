//Dijkstra

#include<Stdio.h>
#include<stdlib.h>

#define vertex_num 5
#define edge_num 8

struct node {
	int v;
	int weight;
	struct node *next;
};

struct dijkstra {
	int found; //최단거리가 알려졌는가 1->yes, 0->no
	int distance;
	int prev_vertex;
};

struct dijkstra dtable[vertex_num]; //초기화 필요
struct node *graph[vertex_num];





void addEdge(int v1, int v2, int w,int doreverse)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->v = v2;
	new_one->next = 0;
	new_one->weight = w;

	struct node *cur = graph[v1];
	if (cur == 0)
	{
		graph[v1] = new_one;
	}
	else
	{
		while (cur->next != 0)
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

void initDtable()
{
	for (int i = 0; i < vertex_num; i++)
	{
		dtable[i].found = 0;
		dtable[i].distance = 99999;
		dtable[i].prev_vertex = -1;
	}
	return;
}

/*
최단 거리가 알려지지 않은 vertex 중에서
distance가 가장 짧은 vertex를 반환한다.
만약 모든 vertex의 최단거리가 알려졌을경우
-1를 반환
*/
int findDijkstraNextVertex()
{
	int i;
	int smallest_distance= 99999; //가장 짧은 거리
	int smallest_vertex=-1; //가장 짧은 거리의 vertex

	for (i = 0; i < vertex_num; i++)
	{
		if (dtable[i].found == 0 && dtable[i].distance < smallest_distance)
		{
			smallest_vertex = i;
			smallest_distance = dtable[i].distance;
		}
	}
	return smallest_vertex;
}

void showDtable()
{
	for (int i = 0; i < vertex_num; i++)
	{
		printf("%d: %d %d %d \n", i, dtable[i].found, dtable[i].distance, dtable[i].prev_vertex);
	}
	return;
}

void update_dtable(int v)
{
	struct node *cur = graph[v];
	while (cur != 0)
	{
		//최단거리가 알려지지 않았고
		//기존 알려진 거리보다, v를 통할 경우 더 가까우면 dtable을 update
		if (dtable[cur->v].found == 0 && 
			dtable[cur->v].distance > dtable[v].distance + cur->weight)
		{
			dtable[cur->v].distance = dtable[v].distance + cur->weight;
			dtable[cur->v].prev_vertex = v;
		}
		cur = cur->next;
	}
}


void doDijkstra(int v)
{
	int next_vertex = -1;

	//시작 vertex의 거리는 항상 0
	dtable[v].distance = 0;
	//dtable 안에 있는 vertex 중, 최단거리가 밝혀지지 않은
	//vertex 중 가장 작은 distance를 찾는다.
	
	while ((next_vertex = findDijkstraNextVertex())!=-1)
	{
		dtable[next_vertex].found = 1; //최단거리 찾았다고 표시
		update_dtable(next_vertex);
	}
	showDtable();
}

int main(void)
{
	//양방향
	addEdge(0, 1, 1,1);
	addEdge(0, 2, 3,1);
	addEdge(0, 4, 5,1);
	addEdge(1, 2, 2,1);
	addEdge(1, 4, 4,1);
	addEdge(2, 4, 6,1);
	addEdge(2, 3, 7,1);
	addEdge(3, 4, 8,1);

	initDtable();

	doDijkstra(0); //0번에서 가지는 모든 최단거리

	return 0;
}