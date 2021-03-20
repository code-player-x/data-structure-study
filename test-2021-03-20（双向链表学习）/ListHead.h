#pragma once
#include<iostream>
#include<assert.h>
#include<stdio.h>
#include<string.h>
typedef int LTDataType;
struct ListNode
{
	struct ListNode* next;
	struct ListNode* prev;
	int data;
};
//����һ����㣬���ؽ���ָ��
ListNode* BuyListNode(LTDataType x);
// �������������ͷ���.
//void ListInit(ListNode** pphead);//��һ�ַ�ʽ
ListNode* ListInit();//�ڶ��ַ�ʽ
// ˫����������
void ListDestory(ListNode** pphead);
void ListClear(ListNode* phead);
// ˫�������ӡ
void ListPrint(ListNode* phead);
// ˫������β��
void ListPushBack(ListNode* phead, LTDataType x);
// ˫������βɾ
void ListPopBack(ListNode* phead);
// ˫������ͷ��
void ListPushFront(ListNode* phead, LTDataType x);
// ˫������ͷɾ
void ListPopFront(ListNode* phead);
// ˫���������
ListNode* ListFind(ListNode* phead, LTDataType x);
// ˫��������pos��ǰ����в���
void ListInsert(ListNode* pos, LTDataType x);
// ˫������ɾ��posλ�õĽڵ�
void ListErase(ListNode* pos);