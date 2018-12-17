#include <iostream>
#include <thread>
#include <omp.h>
#include <algorithm>
#include <ctime>
using namespace std;

int res[100000000];
int temp[100000000];
void myMerge(int l,int r)
{
	int mid = l + (r - l) / 2;
	int p1 = l;
	int p2 = mid;
	int p = 0;
	while (p1 < mid&&p2 < r)
	{
		if (res[p1] < res[p2])
		{
			temp[p++] = res[p1++];
		}
		else
		{
			temp[p++] = res[p2++];
		}
	}
	while (p1 < mid)
	{
		temp[p++] = res[p1++];
	}
	while (p2 < r)
	{
		temp[p++] = res[p2++];
	}
	memcpy(res + l, temp, sizeof(int)*(r - l));
}

void MergeSort(int l,int r)
{
	//底层情况不再递归
	if (r - l <= 25)
	{
		sort(res + l, res + r);
		return;
	}
	int mid = l + (r - l) / 2;
	//数组长度过小时不再创建线程，单线程内跑递归
	if (r - l >= 500000)
	{
		thread tl(MergeSort, l, mid);
		thread tr(MergeSort, mid, r);
		tl.join();
		tr.join();
	}
	else
	{
		MergeSort(l, mid);
		MergeSort(mid, r);
	}
	myMerge(l, r);
}

int main()
{
	int count = 0;
	while (scanf_s("%d",&res[count++])!=EOF);
	//while (cin>>res[count++]);
	clock_t start, finish;
	start = clock();
	MergeSort(0,count-1);
	finish = clock();
	double duration = double(finish - start);
	/*for (int i = 0; i < count-1; i++)
	{
		printf("%d ")
	}*/
	printf("%.0fms",duration);
	return 0;
}