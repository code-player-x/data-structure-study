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
// ����ʵ�ֵĽӿ�
// ��������
void InsertSort(int* a, int n)
{
	//����end��λ�ô�0�ߵ�n-2
	for (int i = 0; i < n - 1; ++i)
	{
		//��������
		//��[0,end]�����в���tmp����������
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
		a[end + 1] = tmp;//�˴�end�Ѿ������պñ�tmpС��λ��

	}


}



// ϣ������
void ShellSort(int* a, int n)
{//gap>1ʱΪԤ����   �ӽ�����
//gap=1ʱΪֱ�Ӳ�������  ����
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;//+1�Ǳ�֤���һ��һ����1,����������2
		for (int i = 0; i < n - gap; ++i)
		{
			//���Ϊgap��������
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
			a[end + gap] = tmp;//�˴�end�Ѿ������պñ�tmpС��λ��
		}
	}
	
	


}


// ѡ������
void SelectSort(int* a, int n)
{
	int begin = 0, end = n - 1;
	while (begin < end)
	{
		//[begin,end]ѡ��һ����С�ģ�ѡ��һ�������±�
		int mini = begin, maxi = end;
		for (int i = begin; i <= end; ++i)
		{
			if (a[i] > a[maxi])
				maxi = i;
			if (a[i] < a[mini])
				mini = i;
		}
		Swap(&a[begin], &a[mini]);
		//����
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
		//ѡ�����Һ����д����һ��
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}
		//��ĺ��Ӻ͸����Ƚ�,������ӱȸ��״󣬽������������µ���
		//�������С�ڸ��� �����������
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
// ������O��N*logN��
void HeapSort(int* a, int n)
{
	//�����򣬽����O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n,i);
	}
	int end = n - 1;
	while (end>0)
	{
		//�ѶѶ���ǰ�����һ�λ������
		Swap(&a[0], &a[end]);
		//����ѡ��ʣ�µ����������
		AdjustDown(a, end, 0);//ȥ���������󣬸պ�end=n-1����
		--end;
		
	}
}


// ð������
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
//����ȡ�п��԰ѿ�������������µĸ��Ӷȴ�O��N*N������O(N*logN)
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
		else if (a[begin] < a[end])//mid  �����ֵ
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

// ��������hoare�汾
int PartSort1(int* a, int begin, int end)//���˿���
{
	//end��key���������/ begin��key���ұ�����
	int key = a[end];
	int keyindex = end;
	while (begin < end)
	{
		//begin�Ҵ�
		while (begin < end&&a[begin] <= key) 
		{
			++begin;
		}
		//end��С
		while (begin<end&&a[end] >= key)
		{
			--end;
		}
		Swap(&a[begin], &a[end]);
	}
	Swap(&a[begin],&a[keyindex]);

	return begin;
}
// ���������ڿӷ��������hoare����һЩ�Ľ���������������ף��Ҳ����׷���
int PartSort2(int* a, int begin, int end)
{
	
	int key = a[end];
	while (begin < end)
	{
		while (begin < end && a[begin] <= key)
		{
			//�ұ��ǿӣ�����Ҵ�
			++begin;
		}
		a[end] = a[begin];//�ҵ����ӵ��ұߵĿ�����ȥ��ͬʱbegin�γ��µĿ�
		while (begin < end && a[end] >= key)
		{
			--end;
		}
		a[begin] = a[end];//�ҵ�С�ӵ���ߵ��¿�����ȥ��ͬʱend�γ��µĿ�
	}
	a[begin] = key;//whileѭ����֮��ض�begin=end
	return begin;

}
// ��������ǰ��ָ�뷨,�߼����ӣ�ʵ�ּ�
int PartSort3(int* a, int begin, int end)
{
	int midIndex = GetMidIndex(a, begin, end);
	Swap(&a[end], &a[midIndex]);
	int key = a[end];
	int prev = begin-1;
	int cur = begin;
	while (cur<end)//cur��end�ͽ���
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
// ��������ݹ�ʵ��
void QuickSort(int* a, int begin, int end)
{
	if (begin >= end)
		return;
	int keyindex = PartSort3(a, begin, end);
	//[begin,keyindex-1]    key   [keyindex+1,end]
	QuickSort(a, begin, keyindex - 1);
	QuickSort(a, keyindex + 1, end);

}
// �������� �ǵݹ�ʵ��(���±�)
void QuickSortNonR(int* a, int begin, int end)
{
	//�������ݽṹջ��ģ��ݹ�
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
	//�Ȼ���
	int mid = (begin + end) >> 1;
	//[begin,mid]  [mid+1,end]  ����
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid+1, end, tmp);

	//[begin,mid]  [mid+1,end]  ����
	//�鲢������������
	int begin1 = begin, end1 = mid;
	int begin2 = mid+1, end2 =end;
	int index = begin;
	while (begin1 <= end1 && begin2 <= end2)//���ǽ�������
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
	//���鲢��tmp�����ݹ鲢��Ԫ����
	memcpy(a + begin, tmp + begin, sizeof(int) * (end-begin+1));
}
// �鲢����ݹ�ʵ��
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(a, 0, n - 1,tmp);
	free(tmp);

}

// �鲢����ǵݹ�ʵ��
void MergeSortNonR(int* a, int n);

// ��������
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
	//1��ͳ�ƴ���
	//2�����ݴ�����������
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
// ������������ܶԱ�
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