#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define strLen 100

//�μ� : ���� ���ڿ�
//��ȯ : lps �迭(�ش� �迭�� �����ּ�)
int *calculate_lps(char *_pattern_str)
{
	int patternLen;
	int *_lps = 0; //lps �迭
	int i, j;

	patternLen = strlen(_pattern_str);
	_lps = (int *)malloc(sizeof(int)*patternLen);

	//LPS�迭 �ʱ�ȭ
	memset(_lps, 0, sizeof(int)*patternLen);

	//lps �迭 ���
	j = 0;
	for (i = 1; i < patternLen; i++)
	{
		while (j > 0 && _pattern_str[i] != _pattern_str[j])
		{
			j = _lps[j - 1];
		}
		if (_pattern_str[i] == _pattern_str[j])
		{
			j++;
			_lps[i] = j;
		}
	}


	return _lps;
}

int main(void)
{
	int i, j;

	//target string
	char target_str[strLen] = "ABABABABBABABABABC";

	//pattern string
	char pattern_str[strLen] = "ABABABABC";

	int target_len;
	int pattern_len;

	int *lps = 0;

	target_len = strlen(target_str);
	pattern_len = strlen(pattern_str);

	//LPS ���ϱ�

	lps = calculate_lps(pattern_str);
	for (int i = 0; i < pattern_len; i++)
	{
		printf("%d---->%d\n", i, lps[i]);
	}

	//------string matching
	printf("---------%s -> %s-------\n", pattern_str, target_str);

	//i : target string.�� ���� ��ġ index
	//j : pattern str�� ���� ��ġ index

	j = 0;
	for (i = 0; i < target_len; i++)
	{
		while (j > 0 && target_str[i] != pattern_str[j])
		{
			j = lps[j - 1];
		}
		if (target_str[i] == pattern_str[j])
		{
			if (j == (pattern_len - 1)) //������ �� ���ߴ�.
			{
				printf("Found matchng at %d\n", (i - pattern_len + 1));
				j = lps[j];
			}
			else
			{
				j++;
			}
		}
	}
	printf("complete!\n");
	return 0;
}
