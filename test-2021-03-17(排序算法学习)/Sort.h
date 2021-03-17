#pragma once
#include<ctime>
#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include<string.h>
void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void Swap(int* p1, int* p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
// 排序实现的接口
// 插入排序
void InsertSort(int* a, int n)
{
	//控制end的位置从0走到n-2
	for (int i = 0; i < n - 1; ++i)
	{
		//单趟排序
		//在[0,end]区间中插入tmp，依旧有序
		int end=i;
		int tmp = a[end + 1];
		while (end >= 0)
		{
			if (a[end] > tmp)
			{
				a[end + 1] = a[end];
				end--;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;//此处end已经减到刚好比tmp小的位置

	}


}



// 希尔排序
void ShellSort(int* a, int n)
{//gap>1时为预排序   接近有序
//gap=1时为直接插入排序  有序
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;//+1是保证最后一次一定是1,除数不能是2
		for (int i = 0; i < n - gap; ++i)
		{
			//间隔为gap的与排序；
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (a[end] > tmp)
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;//此处end已经减到刚好比tmp小的位置
		}
	}
	
	


}


// 选择排序
void SelectSort(int* a, int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		//[begin,end]选出一个最小的，选出一个最大的下标
		int mini = begin, maxi = end;
		for (int i = begin; i <= end; ++i)
		{
			if (a[i] > a[maxi])
				maxi = i;
			if (a[i] < a[mini])
				mini = i;
		}
		Swap(&a[begin], &a[mini]);
		//修正
		if (begin == maxi)
			maxi=mini;
		Swap(&a[end], &a[maxi]);
		++begin;
		--end;
	}

}
void AdjustDown(int *a ,int n,int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child<n)
	{
		//选出左右孩子中大的那一个
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}
		//大的孩子和父结点比较,如果孩子比父亲大，交换，继续向下调整
		//如果孩子小于父亲 ，则调整结束
		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}


}
// 堆排序O（N*logN）
void HeapSort(int* a, int n)
{
	//排升序，建大堆O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n,i);
	}
	int end = n - 1;
	while (end>0)
	{
		//把堆顶当前最大数一次换到最后
		Swap(&a[0], &a[end]);
		//调堆选出剩下的数当中最大
		AdjustDown(a, end, 0);//去掉最大的数后，刚好end=n-1个数
		--end;
		
	}
}


// 冒泡排序
void BubbleSort(int* a, int n)
{
	for (int end = n-1; end>0; end--)
	{
		int flag = 0;
		for (int i = 0; i < end; i++)
		{
			if (a[i]>a[i + 1] )
			{
				Swap(&a[i], &a[i + 1]);
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}


}
//三数取中可以把快排在有序情况下的复杂度从O（N*N）将至O(N*logN)
int GetMidIndex(int* a, int begin, int end)
{
	int mid = (begin + end) >> 1;
	//begin   mid   end
	if (a[begin] < a[mid])
	{
		if (a[mid] < a[end])
		{
			return mid;
		}
		else if (a[begin] < a[end])//mid  是最大值
		{
			return end;
		}
		else
			return begin;
	}
	else//a[begin]>a[mid]
	{
		
			if (a[mid] > a[end])
				return mid;
			else if (a[begin] < a[end])
				return begin;
			else
				return end;
	}
}

// 快速排序hoare版本
int PartSort1(int* a, int begin, int end)//单趟快排
{
	//end做key，左边先走/ begin做key，右边先走
	int key = a[end];
	int keyindex = end;
	while (begin < end)
	{
		//begin找大
		while (begin < end&&a[begin] <= key) 
		{
			++begin;
		}
		//end找小
		while (begin<end&&a[end] >= key)
		{
			--end;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin],&a[keyindex]);

	return begin;
}
// 快速排序挖坑法，相比于hoare，有一些改进，理解起来更容易，且不容易犯错
int PartSort2(int* a, int begin, int end)
{
	
	int key = a[end];
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			//右边是坑，左边找大
			++begin;
		}
		a[end] = a[begin];//找到大扔到右边的坑里面去，同时begin形成新的坑
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		a[begin] = a[end];//找到小扔到左边的新坑里面去，同时end形成新的坑
	}
	a[begin] = key;//while循环完之后必定begin=end
	return begin;

}
// 快速排序前后指针法,逻辑复杂，实现简单
int PartSort3(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midIndex]);
	int key = a[end];
	int prev = begin-1;
	int cur = begin;
	while (cur<end)//cur到end就结束
	{

		if (a[cur] < key&&++prev!=cur)
		{
			Swap(&a[cur],& a[prev]);
		}
		++cur;
	}
	++prev;
	Swap(&a[end], &a[prev]);
	return prev;

}
// 快速排序递归实现
void QuickSort(int* a, int begin, int end)
{
	if (begin >= end)
		return;
	int keyindex = PartSort3(a, begin, end);
	//[begin,keyindex-1]    key   [keyindex+1,end]
	QuickSort(a, begin, keyindex - 1);
	QuickSort(a, keyindex + 1, end);

}
// 快速排序 非递归实现(入下标)
void QuickSortNonR(int* a, int begin, int end)
{
	//借助数据结构栈来模拟递归
	Stack st;
	StackInit(&st);
	StackPush(&st, begin);
	StackPush(&st, end);
	while (!StackEmpty(&st))
	{
		int right = StackTop(&st);
		StackPop(&st);
		int left = StackTop(&st);
		StackPop(&st);

		int keyindex = PartSort3(a, left, right);
		//[left,keyindex]  keyindex  [keyindex+1,right]
		if (left < keyindex-1)
		{
			StackPush(&st, left);
			StackPush(&st, keyindex);

		}
		if (keyindex +1<right)
		{
			StackPush(&st, keyindex + 1);
			StackPush(&st, right);
		}
	}


	StackDestroy(&st);
}
void _MergeSort(int* a, int begin, int end,int*tmp)
{
	if (begin >= end)
		return;
	//先划分
	int mid = (begin + end) >> 1;
	//[begin,mid]  [mid+1,end]  无序
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid+1, end, tmp);

	//[begin,mid]  [mid+1,end]  有序
	//归并两段有序区间
	int begin1 = begin, end1 = mid;
	int begin2 = mid+1, end2 =end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2)//或是结束条件
	{
		if (a[begin1]<a[begin2])
		{
			tmp[index] = a[begin1];
			index++;
			begin1++;
		}
		else
		{
			tmp[index] = a[begin2];
			index++;
			begin2++;
		}
	}
	if (begin1 <= end1)
	{
		while (begin1 <= end1)
		{
			tmp[index] = a[begin1];
			index++;
			begin1++;
		}
	}
	else
	{
		while (begin2<= end2)
		{
			tmp[index] = a[begin2];
			index++;
			begin2++;
		}

	}
	//将归并到tmp的数据归并回元数据
	memcpy(a + begin, tmp + begin, sizeof(int) * (end-begin+1));
}
// 归并排序递归实现
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1,tmp);
	free(tmp);

}

// 归并排序非递归实现
void MergeSortNonR(int* a, int n);

// 计数排序
void CountSort(int* a, int n)
{
	int max = a[0], min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range = max - min + 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	memset(countArr, 0, sizeof(int)*range);
	//1、统计次数
	//2、依据次数进行排序
	for (int i = 0; i < n; i++)
	{
		countArr[a[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < range; ++i)
	{
		while (countArr[i]--)
		{
			a[j++] = i + min;
		}
	}
}



void Test()
{
	int a[] = { 3,6,2,5,7,9,8,6,1,4 };
	//InsertSort(a, sizeof(a) / sizeof(int));
	//ShellSort(a, sizeof(a) / sizeof(int));
	//SelectSort(a, sizeof(a) / sizeof(int));
	//HeapSort(a, sizeof(a) / sizeof(int));
	//BubbleSort(a, sizeof(a) / sizeof(int));
	//QuickSort(a, 0, sizeof(a) / sizeof(int) - 1);
	//QuickSortNonR(a, 0, sizeof(a) / sizeof(int) - 1);
	//MergeSort(a, sizeof(a) / sizeof(int) );
	CountSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));

}
// 测试排序的性能对比
void TestOP()
{
	srand(time(0));
	const int N = 100000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
	}
	int begin1 = clock();
	InsertSort(a1, N);
	int end1 = clock();
	int begin2 = clock();
	ShellSort(a2, N);
	int end2 = clock();
	int begin3 = clock();
	SelectSort(a3, N);
	int end3 = clock();
	int begin4 = clock();
	HeapSort(a4, N);
	int end4 = clock();
	int begin5 = clock();
	//QuickSort(a5, 0, N - 1);
	int end5 = clock();
	int begin6 = clock();
	//MergeSort(a6, N);
	int end6 = clock();
	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	//printf("QuickSort:%d\n", end5 - begin5);
	//printf("MergeSort:%d\n", end6 - begin6);
	free(a1);
	free(a2);   
	free(a3);
	free(a4);
	free(a5);
	free(a6);
}