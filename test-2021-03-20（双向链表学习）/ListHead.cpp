#include"ListHead.h"
ListNode* BuyListNode(LTDataType x)
{
	ListNode* node = (ListNode*) new ListNode;
	node->next = NULL;
	node->prev = NULL;
	node->data = x;
	return node;
}
// ˫�������ӡ
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
// �������������ͷ���.
//void ListInit(ListNode** pphead)
//{
//      *pphead = BuyListNode(0);
//      (*pphead)->next = *pphead;//*��������->���ȼ���ͬ�����Ҫ������
//      (*pphead)->prev = *pphead;
//
//}
ListNode* ListInit()//�ڶ��ַ�ʽ
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
// ˫������βɾ
void ListPopBack(ListNode* phead)
{
	//assert(phead);
	//assert(phead->next != phead);//�ж��Ƿ�λ������
	//ListNode* tail = phead->prev;
	//ListNode* tailPrev = tail->prev;
	//tailPrev->next = phead;
	//phead->prev = tailPrev;
	//free(tail);
	//tail = NULL;
	ListErase(phead->prev);
}
// ˫������ͷ��
void ListPushFront(ListNode* phead, LTDataType x)
{
	assert(phead);
	//if (phead->next == phead)//û��Ҫ�жϣ���Ϊ���Ǵ�ͷ˫��ѭ�����������
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
// ˫������ͷɾ
void ListPopFront(ListNode* phead)
{
	//assert(phead);
	//assert(phead->next != phead);//�ж��Ƿ�λ������
	//ListNode* first = phead->next;
	//ListNode*second = first->next;
	//phead->next = second;
	//second->prev = phead;
	//free(first);
	//first = NULL;
	ListErase(phead->next);
}
// ˫���������
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
// ˫��������pos��ǰ����в���
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
// ˫������ɾ��posλ�õĽڵ�
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
// ˫����������
void ListDestory(ListNode** pphead)
{
	assert(*pphead);
	ListClear(*pphead);
	//����
	free(*pphead);
	*pphead = NULL;
}
//�����������ݽ�㣬����ͷ��㣬���Լ���ʹ��
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