
/**
input 2 string on console
output longest_common_substring_noncontinuous
*/

#include <stdio.h>
#include <stdlib.h>


#define MAX_STR_LEN 10000
char str1[MAX_STR_LEN], str2[MAX_STR_LEN];
char result[MAX_STR_LEN];

#define Array2(arr, col_count, i, j) arr[(col_count) * (i) + (j)]

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

int main()
{
	scanf("%s%s", str1, str2);
	int len1 = strlen(str1);
	int len2 = strlen(str2);

	unsigned int *arr = (unsigned int*)calloc(len1 * len2, sizeof(unsigned int));

	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			if (str1[i] == str2[j])
			{
				if (i * j > 0)
				{
					Array2(arr, len2, i, j) = Array2(arr, len2, i - 1, j - 1) + 1;
				}
				else
				{
					Array2(arr, len2, i, j) = 1;
				}
			}
			else
			{
				int best_1 = i > 0 ? Array2(arr, len2, i - 1, j) : 0;
				int best_2 = j > 0 ? Array2(arr, len2, i, j - 1) : 0;
				Array2(arr, len2, i, j) = max(best_1, best_2);
			}
		}
	}

	for (int i = 0; i < len1; ++i)
	{
		for (int j = 0; j < len2; ++j)
		{
			printf("%d ", Array2(arr, len2, i, j));
		}
		printf("\n");
	}

	int i = len1 - 1, j = len2 - 1;
	int resLen = Array2(arr, len2, i, j);
	result[resLen] = 0;

	do 
	{
		if (str1[i] == str2[j])
		{
			result[--resLen] = str1[i];
			i--;
			j--;
		}
		else
		{
			int best_1 = i > 0 ? Array2(arr, len2, i - 1, j) : 0;
			int best_2 = j > 0 ? Array2(arr, len2, i, j - 1) : 0;

			if (best_1 > best_2)
				i--;
			else
				j--;
		}

	} while (i >=0 && j >=0);
	

	printf("%s", result);

	free(arr);

	return 0;
}