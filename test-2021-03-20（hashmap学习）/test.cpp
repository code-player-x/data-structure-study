//#include<iostream>
//#include<unordered_set>
//#include<unordered_map>
//#include<map>
//#include<set>
//#include<string>
//#include<ctime>
//using namespace std;
//
//void test_unordered_map_set()
//{
//	unordered_set<int> us;
//	us.insert(4);
//	us.insert(2);
//	us.insert(1);
//	us.insert(5);
//	us.insert(6);
//	us.insert(2);//能去重，但不能排序
//	//set 排序+去重
//
//	unordered_set<int>::iterator it= us.begin();
//	while (it != us.end())
//	{
//		cout << *it << " ";
//		++it;
//	}
//	cout << endl;
//
//	//unordered_map<string, string>dict;
//	map<string, string>dict;
//
//	dict.insert(make_pair("sort", "排序"));
//	dict["string"] = "字符串";
//	dict.insert(make_pair("left", "左边"));
//
//	//unordered_map<string, string>::iterator dit = dict.begin();
//	map<string, string>::iterator dit = dict.begin();
//
//	while (dit != dict.end())
//	{
//		cout << dit->first << dit->second << endl;
//		++dit;
//	}
//	cout << endl;
//
//}
//
//void test_op()//map、set、unordered_map和unordered_set性能对比
//{
//	unordered_set<int> us;
//	set<int>s;
//
//	const int n = 100000;
//	vector<int> v;
//	v.reserve(n);
//	srand(time(0));
//	for (size_t i = 0; i < n; ++i)
//	{
//		v.push_back(rand());
//	}
//
//	size_t begin1 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		us.insert(v[i]);
//	}
//	size_t end1 = clock();
//	cout << "unordered_set insert:" << end1 - begin1 << endl;
//
//	size_t begin2 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		s.insert(v[i]);
//	}
//	size_t end2 = clock();
//	cout << "set insert:" << end2 - begin2 << endl;
//
//
//	size_t begin3 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		us.find(v[i]);
//	}
//	size_t end3 = clock();
//	cout << "unordered_set find:" << end3 - begin3 << endl;
//
//	size_t begin4 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		s.find(v[i]);
//	}
//	size_t end4 = clock();
//	cout << "set find:" << end4 - begin4 << endl;
//
//	size_t begin5 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		us.erase(v[i]);
//	}
//	size_t end5 = clock();
//	cout << "unordered_set erase:" << end5 - begin5 << endl;
//
//	size_t begin6 = clock();
//	for (size_t i = 0; i < n; ++i)
//	{
//		s.erase(v[i]);
//	}
//	size_t end6 = clock();
//	cout << "set erase:" << end6 - begin6 << endl;
//}
//
//
//int main()
//{
//
//	//test_unordered_map_set();
//	test_op();
//	return 0;
//}

#include"HashTable.h"

int main()
{
	OPEN_HASH::TestHashTable();

	return 0;
}

