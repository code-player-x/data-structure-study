#pragma once
#include<iostream>
#include "RBTree.h"
namespace px
{
	template<class K>

	class set
	{
	
		struct SetKeyOfT//仿函数
		{
			const K & operator()(const K& k)
			{
				return k;
			}
		};
	public:
 		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;
		//typename告诉编译器 RBTree<K, K, SetKeyOfT>::iterator是一个类型的名称,现在可以不用找，之后再找
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{ 
			return _t.end();

		}
		pair<iterator, bool> Insert(const K& k)
		{
			return _t.Insert(k);

		}

	private:
		RBTree<K, K, SetKeyOfT>_t;
	};


	void test_set()
	{
		set<int>s;
		s.Insert(3);
		s.Insert(4);

		s.Insert(1);
		s.Insert(2);
		s.Insert(5);

		set<int>::iterator it = s.begin();
		while (it != s.end())
		{
			cout << *it << "  ";
			++it;
		}
		cout << endl;
	}


}