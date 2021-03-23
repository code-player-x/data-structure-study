#pragma once
#include<iostream>
#include "RBTree.h"
#include<string>
namespace px
{
	template<class K,class V>

	class map
	{
		struct MapKeyOfT//�º�����ʵ����map��pair��first��ֵ���Ƚ�
		{
			const K & operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename RBTree<K, pair<K,V>,MapKeyOfT>::iterator iterator;
		//typename���߱����� RBTree<K, K, SetKeyOfT>::iterator��һ�����͵�����,���ڿ��Բ����ң�֮������
		iterator begin()
		{
			return _t.begin();
		}
		iterator end()
		{
			return _t.end();

		}
		
		pair<iterator,bool> Insert(const pair<K,V>& kv)
		{
			return _t.Insert(kv);
			 
		}
		V& operator[](const K&key)
		{
			pair<iterator,bool> ret=_t.Insert(make_pair(key, V()));
			return ret.first->second; 
		}



	private:
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};


	void test_map()
	{
		//map<int, int> m;
		//m.Insert(make_pair(1, 1));
		//m.Insert(make_pair(3, 3));
		//m.Insert(make_pair(10, 10));
		//m.Insert(make_pair(5, 5));
		//m.Insert(make_pair(6, 6));

		//map<int, int> ::iterator it = m.begin();
		//while (it != m.end())
		//{
		//	cout << it->first << " :" << it->second << endl;
		//	++it;
		//}
		//cout << endl;
		//for (auto kv : m)
		//{
		//	cout <<kv.first << " :" << kv.second << endl;

		//}
		//cout << endl;




		string strs[] = { "����", "ӣ��", "����", "ƻ��", "����", "����", "����", "ƻ��" };
		map<string, int> countMap;
		for (auto& str : strs)
		{	//1�����ˮ������map�У���operator[]�����pair<str��0>������ӳ�����(����)�����ý�����++��
			//2�����ˮ����map�У���operator[]����ˮ����Ӧ��ӳ�����(����)�����ã�����++��
			countMap[str]++;

		} 
		for (auto kv : countMap)
			{
				cout <<kv.first << " :" << kv.second << endl;

			}
			cout << endl;
	}
}