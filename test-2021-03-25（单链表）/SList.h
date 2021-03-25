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

void SListPushBack(SListNode** pphead, SListDateType x);//Ҫ�ı䴫��ȥ��ָ������������ö���ָ��
void SListPopBack(SListNode** pphead);//��Ϊβɾ���ܻ�ɾ���գ�Ҫ��ͷָ��ı�ΪNULL�����Ի��ö���ָ��

void SListPushFront(SListNode** pphead, SListDateType x);
void SListPopFront(SListNode** pphead);


SListNode* SListFind(SListNode* phead, SListDateType x);
void SListPrint(SListNode* phead);

SListNode* SListInsertAfter(SListNode* pos, SListDateType x);
SListNode* SListEraseAfter(SListNode* pos);
