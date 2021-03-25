#include"SList.h"
#include<iostream>
using namespace std;
SListNode* BuySListNde(SListDateType x)
{
	SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
	if (newNode == NULL)
	{
		cout << "申请结点失败" << endl;
		exit(-1);
	}
	newNode->data = x;
	newNode->next = NULL;

	return newNode;
}
void SListPushBack(SListNode** pphead, SListDateType x)
{
	SListNode* newNode = BuySListNde(x);
	if (*pphead == NULL)
	{
		
		*pphead = newNode;
	}
	else
	{
		//找尾巴
		SListNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
		if (newNode == NULL)
		{
			cout << "申请结点失败" << endl;
			exit(-1);
		}
		newNode->data = x;
		newNode->next = NULL;
		tail->next = newNode;
	}
	
	

}



void SListPopBack(SListNode** pphead)
{
	//1 ·空
	//2 ·一个结点
	//3 ·一个以上结点
	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SListNode* prev = NULL;
		SListNode* tail = *pphead;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		prev->next = NULL;
	}
}
//头插法
void SListPushFront(SListNode** pphead, SListDateType x)
{
	SListNode* newNode = BuySListNde(x);
	newNode->next = *pphead;
	*pphead = newNode;

}
void SListPopFront(SListNode** pphead)
{
	//1 ·空
	//2 ·一个结点(可以和3合并)
	//3 ·一个以上结点
	if (*pphead == NULL)
	{
		return;
	}

	else
	{
		SListNode* next = (*pphead)->next;

		free(*pphead);
		*pphead = next;
	}


}

//单链表查找
SListNode* SListFind(SListNode* phead, SListDateType x)
{
	SListNode* cur = phead;
	while (cur)//cur!=0
	{
		if (cur->data == x)
		{
			return cur;
		}
		cur = cur->next;
	}
	return NULL;




}
void SListPrint(SListNode* phead)
{
	SListNode* cur = phead;
	while (cur != NULL)
	{
		cout << cur->data << "-> ";
		cur = cur->next;
	}
	cout << "NULL" << endl;;
}
SListNode* SListInsertAfter(SListNode* pos, SListDateType x)
{
	assert(pos);

	SListNode* newnode = BuySListNde(x);
	newnode->next = pos->next;
	pos->next = newnode;



}

SListNode* SListEraseAfter(SListNode* pos)
{
	assert(pos);
	if (pos->next != NULL)
	{
		//pos->next = pos->next->next;不推荐
		SListNode* next = pos->next;
		SListNode* nextnext = next->next;
		pos->next = nextnext;
		free(next);
	}


}
