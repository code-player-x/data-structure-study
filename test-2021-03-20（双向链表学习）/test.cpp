#include"ListHead.h"
using namespace std;
void TestList01()
{
	//ListNode* phead = NULL;
	//ListInit(&phead);
	ListNode* phead = ListInit();
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPushBack(phead, 4);
	ListPrint(phead);
	ListPopBack(phead);
	ListPrint(phead);
	ListPushFront(phead, 5);//ͷ�����
	ListPushFront(phead, 6);//ͷ�����
	ListPrint(phead);
	ListPopFront(phead);//ͷɾ����
	ListPrint(phead);
	ListDestory(&phead);
}
void TestList02()
{
	ListNode* phead = ListInit();
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPushBack(phead, 4);
	ListPrint(phead);
	ListNode* pos = ListFind(phead, 3);
	ListInsert(pos, 30);
	ListInsert(pos, 40);
	ListPrint(phead);
	ListErase(pos);
	ListPrint(phead);
	ListDestory(&phead);
}
int main()
{
	TestList02();
	return 0;
}