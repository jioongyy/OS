#include <iostream>
#include <thread>
#include <omp.h>
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
	
	if (r - l == 1)	return;
	int mid = l + (r - l) / 2;
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
	MergeSort(0,count-1);
	/*for (int i = 0; i < count-1; i++)
	{
		printf("%d ")
	}*/
	printf("done");
	return 0;

}