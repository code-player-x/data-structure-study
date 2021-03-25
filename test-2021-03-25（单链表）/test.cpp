#include<iostream>
#include<vector>
#include"SList.h"
using namespace std;
void TestSList()
{
	//SListNode* phead = NULL;
	SListNode* pList = NULL;
	SListPushBack(&pList, 1);
	SListPushBack(&pList, 2);
	SListPushBack(&pList, 3);
	SListPushBack(&pList, 4);

	SListPopBack(&pList);
	SListPopBack(&pList);

	SListPopBack(&pList);

	SListPopBack(&pList);

	SListPopBack(&pList);

	SListPrint(pList);

	SListPushFront(&pList, 1);
	SListPushFront(&pList, 2);
	SListPushFront(&pList, 3);
	SListPushFront(&pList, 4);
	SListPushFront(&pList, 5);

	SListPrint(pList);
	SListPopFront(&pList);
	SListPrint(pList);
	SListNode* pos = SListFind(pList, 3);
	if (pos)
	{ 
		pos->data = 30;


	}
	SListPrint(pList);


}


int main()
{
	
	TestSList();
	return 0;
}








