#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
typedef int SListDateType;
typedef struct SListNode
{
	SListDateType data;
	struct SListNode* next;
}SListNode;

void SListPushBack(SListNode** pphead, SListDateType x);//要改变传过去的指针变量，所以用二级指针
void SListPopBack(SListNode** pphead);//因为尾删可能会删到空，要把头指针改变为NULL，所以还用二级指针

void SListPushFront(SListNode** pphead, SListDateType x);
void SListPopFront(SListNode** pphead);


SListNode* SListFind(SListNode* phead, SListDateType x);
void SListPrint(SListNode* phead);

SListNode* SListInsertAfter(SListNode* pos, SListDateType x);
SListNode* SListEraseAfter(SListNode* pos);
