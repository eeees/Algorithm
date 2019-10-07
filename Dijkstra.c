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
	int found; //�ִܰŸ��� �˷����°� 1->yes, 0->no
	int distance;
	int prev_vertex;
};

struct dijkstra dtable[vertex_num]; //�ʱ�ȭ �ʿ�
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
�ִ� �Ÿ��� �˷����� ���� vertex �߿���
distance�� ���� ª�� vertex�� ��ȯ�Ѵ�.
���� ��� vertex�� �ִܰŸ��� �˷��������
-1�� ��ȯ
*/
int findDijkstraNextVertex()
{
	int i;
	int smallest_distance= 99999; //���� ª�� �Ÿ�
	int smallest_vertex=-1; //���� ª�� �Ÿ��� vertex

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
		//�ִܰŸ��� �˷����� �ʾҰ�
		//���� �˷��� �Ÿ�����, v�� ���� ��� �� ������ dtable�� update
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

	//���� vertex�� �Ÿ��� �׻� 0
	dtable[v].distance = 0;
	//dtable �ȿ� �ִ� vertex ��, �ִܰŸ��� �������� ����
	//vertex �� ���� ���� distance�� ã�´�.
	
	while ((next_vertex = findDijkstraNextVertex())!=-1)
	{
		dtable[next_vertex].found = 1; //�ִܰŸ� ã�Ҵٰ� ǥ��
		update_dtable(next_vertex);
	}
	showDtable();
}

int main(void)
{
	//�����
	addEdge(0, 1, 1,1);
	addEdge(0, 2, 3,1);
	addEdge(0, 4, 5,1);
	addEdge(1, 2, 2,1);
	addEdge(1, 4, 4,1);
	addEdge(2, 4, 6,1);
	addEdge(2, 3, 7,1);
	addEdge(3, 4, 8,1);

	initDtable();

	doDijkstra(0); //0������ ������ ��� �ִܰŸ�

	return 0;
}