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
//创建一个结点，返回结点的指针
ListNode* BuyListNode(LTDataType x);
// 创建返回链表的头结点.
//void ListInit(ListNode** pphead);//第一种方式
ListNode* ListInit();//第二种方式
// 双向链表销毁
void ListDestory(ListNode** pphead);
void ListClear(ListNode* phead);
// 双向链表打印
void ListPrint(ListNode* phead);
// 双向链表尾插
void ListPushBack(ListNode* phead, LTDataType x);
// 双向链表尾删
void ListPopBack(ListNode* phead);
// 双向链表头插
void ListPushFront(ListNode* phead, LTDataType x);
// 双向链表头删
void ListPopFront(ListNode* phead);
// 双向链表查找
ListNode* ListFind(ListNode* phead, LTDataType x);
// 双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, LTDataType x);
// 双向链表删除pos位置的节点
void ListErase(ListNode* pos);