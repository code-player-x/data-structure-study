#include"ListHead.h"
ListNode* BuyListNode(LTDataType x)
{
	ListNode* node = (ListNode*) new ListNode;
	node->next = NULL;
	node->prev = NULL;
	node->data = x;
	return node;
}
// 双向链表打印
void ListPrint(ListNode* phead)
{
	assert(phead);
	ListNode* cur = phead->next;
	while (cur != phead)
	{
		printf("<--%d-->", cur->data);

		cur = cur->next;
	}
	printf("\n");
}
// 创建返回链表的头结点.
//void ListInit(ListNode** pphead)
//{
//      *pphead = BuyListNode(0);
//      (*pphead)->next = *pphead;//*解引用与->优先级相同，因此要加括号
//      (*pphead)->prev = *pphead;
//
//}
ListNode* ListInit()//第二种方式
{
	ListNode* phead = BuyListNode(0);
	phead->next = phead;
	phead->prev = phead;
	return phead;
}
void ListPushBack(ListNode* phead, LTDataType x)
{
	//assert(phead);
	//ListNode* tail = phead->prev;
	//ListNode* newnode = BuyListNode(x);
	//
	////phead.... tail  newnod
	//tail->next = newnode;
	//newnode->prev = tail;
	//newnode->next = phead;
	//phead->prev = newnode;
	//tail = newnode;
	ListInsert(phead, x);
}
// 双向链表尾删
void ListPopBack(ListNode* phead)
{
	//assert(phead);
	//assert(phead->next != phead);//判断是否位空链表
	//ListNode* tail = phead->prev;
	//ListNode* tailPrev = tail->prev;
	//tailPrev->next = phead;
	//phead->prev = tailPrev;
	//free(tail);
	//tail = NULL;
	ListErase(phead->prev);
}
// 双向链表头插
void ListPushFront(ListNode* phead, LTDataType x)
{
	assert(phead);
	//if (phead->next == phead)//没必要判断，因为这是带头双向循环链表的优势
	//{
	//      ListNode* newnode = BuyListNode(x);
	//      phead->next = newnode;
	//      phead->prev = newnode;
	//      newnode->prev = phead;
	//      newnode->next = phead;
	//      ListNode* first = newnode;
	//}
	//ListNode* first = phead->next;
	//ListNode* newnode = BuyListNode(x);
	////phead.... head  newnod
	//phead->next = newnode;
	//newnode->prev = phead;
	//newnode->next = first;
	//first->prev = newnode;
	ListInsert(phead->next, x);
}
// 双向链表头删
void ListPopFront(ListNode* phead)
{
	//assert(phead);
	//assert(phead->next != phead);//判断是否位空链表
	//ListNode* first = phead->next;
	//ListNode*second = first->next;
	//phead->next = second;
	//second->prev = phead;
	//free(first);
	//first = NULL;
	ListErase(phead->next);
}
// 双向链表查找
ListNode* ListFind(ListNode* phead, LTDataType x)
{
	assert(phead);
	ListNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
			return cur;
		cur = cur->next;
	}
	return NULL;
}
// 双向链表在pos的前面进行插入
void ListInsert(ListNode* pos, LTDataType x)
{
	assert(pos);
	ListNode* posPrev = pos->prev;
	ListNode* newnode = BuyListNode(x);
	posPrev->next = newnode;
	newnode->prev = posPrev;
	newnode->next = pos;
	pos->prev = newnode;
}
// 双向链表删除pos位置的节点
void ListErase(ListNode* pos)
{
	assert(pos);
	//assert(pos!=phead);
	ListNode* posPrev = pos->prev;
	ListNode* posNext = pos->next;
	free(pos);
	posPrev->next = posNext;
	posNext->prev = posPrev;
}
// 双向链表销毁
void ListDestory(ListNode** pphead)
{
	assert(*pphead);
	ListClear(*pphead);
	//销毁
	free(*pphead);
	*pphead = NULL;
}
//清理所有数据结点，保留头结点，可以继续使用
void ListClear(ListNode* phead)
{
	assert(phead);
	ListNode* cur = phead;
	while (cur != phead)
	{
		ListNode* next = cur->next;
		free(cur);
		cur = next;
	}
	phead->next = phead;
	phead->prev = phead;
}