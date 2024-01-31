#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rec(int num)
{
	if (num == 0)
		return 0;
	else if (num == 1)
		return 1;
	return rec(num - 1) + rec(num - 2);
}

int dp(int arr[], int num)
{
	if (num <= 1)
		return num;
	if (arr[num] != -1)
		return arr[num];
	return arr[num] = dp(arr, num - 1) + dp(arr, num - 2);
}

int tab(int num)
{
	int first = 0;
	int second = 1;
	for (int num = 0; num < num; num++)
	{
		int temp = first + second;
		first = second;
		second = temp;
	}
	return first;
}

int main(int argc, char const *argv[])
{
	int num = atoi(argv[1]);
	char *filename = "output.txt";
	FILE *fp = fopen(filename, "a");
	int *arr = (int *)malloc((num + 1) * sizeof(int));
	arr[0] = 0, arr[1] = 1;
	for (int j = 2; j <= num; j++)
		arr[j] = -1;
	clock_t t;
	t = clock();
	int recAns = rec(num);
	t = clock() - t;
	double time_taken_rec = ((double)t) / CLOCKS_PER_SEC;
	t = clock();
	int dpAns = dp(arr, num);
	t = clock() - t;
	double time_taken_dp = ((double)t) / CLOCKS_PER_SEC;
	t = clock();
	int tabAns = tab(num);
	t = clock() - t;
	double time_taken_tab = ((double)t) / CLOCKS_PER_SEC;
	fprintf(fp, "%d %d %f %d %f %d %f\n", num, recAns, time_taken_rec, dpAns, time_taken_dp, tabAns, time_taken_tab);
	free(arr);
	fclose(fp);
	return 0;
}
