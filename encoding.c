/*
���� ����

������ ���� ������ ���ڵ��� ���ڿ� �����͸� �Է¹޾�,
���ڵ��Ͽ� ������ ����Ͻÿ�.

���ڵ��� ������ ���ĺ� ��ҹ��ڷ� �̷���� ���ڿ��̸�,
���ڿ��� ���� ���� ������ ������ �ִ� 9�� �̴�.

���� ��� ������ ���� ���ڿ� (�ִ���̴� 1000)�� �ԷµǸ�,
�ǹ̴� ������ ����.

3a200b11c201$00001101#

3: ���ڵ��� ���� ������ ����. (�ִ� 9)
a200: ���� a�� 2���� �ڵ� 00���� ���ڵ�
b11 : ���� b�� 1���� �ڵ� 1���� ���ڵ�
c201: ���� c�� 2���� �ڵ� 01�� ���ڵ���
(�ڵ��� �ִ� ���̴� 9)

$ : ���ڵ��� ������ ����
00 --> a�� ���ڵ�
00 --> a�� ���ڵ�
1 --> b�� ���ڵ�
1 --> b�� ���ڵ�
01 --> c�� ���ڵ�
# : ���ڵ��� ������ ��

���ڵ� �����
aabbc �� ���

�Է�
3a200b11c201$00001101#
���
aabbc

*/



/*
���� ����
�ִ� 9���� �ٸ� ���ĺ� �ҹ��ڷ� ������ ���ڿ� (�ִ���� 50)�� �Է¹޾�,
�̸� ������ ���ڵ��� ���·� ����Ͻÿ�.

���� ���,
���ڿ� aaabbc �� �ԷµǸ�,
�� ���ڼ� ���� �󵵼��� �ľ��Ѵ�.
a:3��, b:2��, c: 1��

������Ʈ���� ������ ���ĺ� ������ ���� �� (b�� c���� ������ ������)��
���� �ڽ����� ���� �����ϰ�,
����, 2�� �̻��� ���ڰ� ������ ������ ������ Ʈ���� ����� ���,
���� ������ ���� ���ĺ��� ������ ��带 ���� �ڽ����� ���´�.

�̿� ����, ������ ������ �ڵ�� �Ʒ��� ����.
a : 0
b : 10
c : 11

�� ������ �̿��Ͽ�, ���ڵ��� ���´�
3a10b210c211$000101011# �� �Ǿ�� �Ѵ�.

������ Ʈ�� ������ ���ڵ��� ���Խ�ų ����
���ĺ� �������� (a->b->c)�� ���� �ִ´�.
�Է�
aaabbc
���
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
		//SLL�� ����.
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

	//�󵵼� üũ
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
