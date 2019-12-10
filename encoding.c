/*
문제 설명

다음과 같이 허프만 인코딩된 문자열 데이터를 입력받아,
디코딩하여 내용을 출력하시오.

인코딩된 내용은 알파벳 대소문자로 이루어진 문자열이며,
문자열에 사용된 문자 종류의 개수는 최대 9개 이다.

예를 들어 다음과 같은 문자열 (최대길이는 1000)이 입력되면,
의미는 다음과 같다.

3a200b11c201$00001101#

3: 인코딩된 문자 종류의 개수. (최대 9)
a200: 문자 a는 2개의 코드 00으로 인코딩
b11 : 문자 b는 1개의 코드 1으로 인코딩
c201: 문자 c는 2개의 코드 01로 인코딩됨
(코드의 최대 길이는 9)

$ : 디코딩할 내용의 시작
00 --> a로 디코딩
00 --> a로 디코딩
1 --> b로 디코딩
1 --> b로 디코딩
01 --> c로 디코딩
# : 디코딩할 내용의 끝

디코딩 결과로
aabbc 를 출력

입력
3a200b11c201$00001101#
출력
aabbc

*/



/*
문제 설명
최대 9개의 다른 알파벳 소문자로 구성된 문자열 (최대길이 50)을 입력받아,
이를 허프만 인코딩한 형태로 출력하시오.

예를 들어,
문자열 aaabbc 가 입력되면,
각 문자수 별로 빈도수를 파악한다.
a:3개, b:2개, c: 1개

허프만트리를 구성할 알파벳 순서가 빠른 것 (b는 c보다 순서가 빠르다)을
왼쪽 자식으로 놓고 구성하고,
만약, 2개 이상의 문자가 합쳐진 노드들을 허프만 트리로 만드는 경우,
가장 순서가 빠른 알파벳을 포함한 노드를 왼쪽 자식으로 놓는다.

이에 따라, 구성된 허프만 코드는 아래와 같다.
a : 0
b : 10
c : 11

위 정보를 이용하여, 인코딩한 형태는
3a10b210c211$000101011# 이 되어야 한다.

허프만 트리 정보를 인코딩에 포함시킬 때는
알파벳 오름차순 (a->b->c)에 따라 넣는다.
입력
aaabbc
출력
3a10b210c211$000101011#
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define num_ASCII 256
#define buf_num 1000

char codeBuf[100];
int codeBufIdx = -1;
int count = 0;
char *symCode[256];
int length[256];
int cnt = 0;
char symbol[100];
struct symbol {
	char c;
	int ascii_num;
	struct symbol *next;
};

struct node{
	char c;
	int freq;
	struct node *next;
	struct node *right;
	struct node *left;
};


struct node *head = 0;
struct symbol *symHead = 0;

struct node *createNode(char _c, int f)
{
	struct node *new_one = (struct node *)malloc(sizeof(struct node));
	new_one->c = _c;
	new_one->freq = f;
	new_one->next = 0;
	new_one->left = 0;
	new_one->right = 0;

	return new_one;
}


void buildSLL(struct node *new_one)
{
	struct node *cur = head;
	if (head == 0)
	{
		head = new_one;
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

struct node *findLeast()
{
	struct node *cur = head;
	struct node *leastOne = 0;
	int leastFreq = 100000;

	while (cur != 0)
	{
		if (cur->freq < leastFreq)
		{
			leastFreq = cur->freq;
			leastOne = cur;
		}
		cur = cur->next;
	}
	if (head == leastOne)
	{
		head = head->next;
	}
	else
	{
		cur = head;
		while (cur->next != leastOne)
		{
			cur = cur->next;
		}
		cur->next = leastOne->next;
	}
	leastOne->next = 0;
	return leastOne;
}


void travelHuff(struct node *n, char _code)
{
	codeBufIdx++;
	codeBuf[codeBufIdx] = _code;
	codeBuf[codeBufIdx + 1] = 0;
	char *codeInfo[2];

	if (n->left == 0 && n->right == 0)
	{
		length[(int)n->c] = (int)strlen(codeBuf);
		//printf("%s\n", symCode[(int)n->c]);
		strcpy(&symCode[(int)n->c], codeBuf);
		symbol[cnt] = n->c;
		cnt++;
	}
	else
	{
		travelHuff(n->left, '0');
		travelHuff(n->right, '1');
	}
	codeBuf[codeBufIdx] = 0;
	codeBufIdx--;

	return;
}

void swap(struct symbol *a, struct symbol *b)
{
	char temp = a->c;
	a->c = b->c;
	b->c = temp;
	return;
}

void bubbleSort()
{
	struct symbol *temp = symHead;
	struct symbol *finish=0;
	if (temp == 0)
	{
		return;
	}
	else
	{
		while (temp->next != finish)
		{
			if ((int)temp->c > (int)temp->next->c)
			{
				swap(temp, temp->next);
			}
			temp = temp->next;
		}
		finish = temp;
	}
}
void checkSymbol(char c)
{
	struct symbol *temp = symHead;
	struct symbol *new_one = (struct symbol*)malloc(sizeof(struct symbol));
	new_one->c = c;
	new_one->next = 0;

	if (symHead == 0)
	{
		symHead = new_one;
		count++;
	}
	else
	{
		while (1)
		{
			if (temp == 0)
			{
				break;
			}
			if (new_one->c == temp->c)
			{
				return;
			}
			temp = temp->next;
		}
		//SLL에 없다.
		temp = symHead;
		while (temp->next != 0)
		{
			temp = temp->next;
		}
		temp->next = new_one;
		count++;
	}

	return;
}


int main(void)
{
	char buf[50];
	memset(buf, 0, sizeof(char)*50);
	gets(buf);
	
	for (int i = 0; i < strlen(buf); i++)
	{
		checkSymbol(buf[i]);
	}

	//빈도수 체크
	int char_cnt[256];
	memset(char_cnt, 0, sizeof(int) * 256);

	for (int i = 0; i < strlen(buf); i++)
	{
		char_cnt[buf[i]]++;
	}

	for (int i = 0; i < 256; i++)
	{
		if (char_cnt[i] > 0)
		{
			buildSLL(createNode(i, char_cnt[i]));
		}
	}

	while (1)
	{
		if (head->next == 0)
		{
			break;
		}
		else
		{
			int small1;
			int small2;
			struct node *a = findLeast();
			struct node *b = findLeast();
			struct node *c = createNode(' ', a->freq + b->freq);

			small1 = (int)a->c;
			small2 = (int)b->c;
			
			if (small2 < small1 && small1)// != (int)' ' && small2 != (int)' ')
			{
				c->left = b;
				c->right = a;
				c->c = b->c;
			}
			else
			{
				c->left = a;
				c->right = b;
				c->c = a->c;
			}

			buildSLL(c);
		}
	}
	travelHuff(head->left, '0');
	travelHuff(head->right, '1');
	

#if 1

	printf("%d", count);
	for (int i = 0; i < count; i++)
	{
		printf("%c%d%s", symbol[i], length[(int)symbol[i]], &symCode[(int)symbol[i]]);

	}
	printf("$");
	for (int i = 0; i < strlen(buf); i++)
	{
		printf("%s", &symCode[buf[i]]);
	}

	printf("#\n");
#endif

	return 0;
}
