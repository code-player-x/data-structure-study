#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K>
struct SetKeyOfT
{
	const K& operator()(const K& key)
	{
		return key;
	}
};
namespace CLOSE_HASH
{

enum State
{
	EMPTY,//空
	EXITS,//存在
	DELETE,//删除
};
template<class T>
struct HashData
{
	T _data;
	State _state;//状态，表示该位置是空，还是删除后为空
};

//unordered_set<K>    ->HashTable<K,K>
//unordered_map<K,V>  ->HashTable<K,pair<K,V>>
template<class K,class T,class KeyOfT>
class HashTable
{ 
	typedef	HashData<T> HashData;
public:
	bool Insert(const T& d)
	{
		//负载因子=表中数据个数/表的大小  衡量哈希表满的程度
		//表接近满，插入数据越容易冲突，冲突越多，效率越低
		//哈希表并不是满了才增容，开放定址法中,一般负载因子到了0.7左右就开始增容
		//负载因子越小，冲突概率越低，整体效率越高，但是负载因子越小，浪费的空间越大
		//所以负载因子一般取一个折中值
		KeyOfT koft;

		if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)
		{
			//增容 
			//1、开2倍大小的新表
			//2、遍历旧表的数据，重新计算在新表中的位置
			//3、释放旧表 
			//vector<HashData>newtables;
			HashTable<K, T, KeyOfT>newht;
			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			newht._tables.resize(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{	//新思路
				if (_tables[i]._state == EXITS)
				{
					newht.Insert(_tables[i]._data);
				}

				//if (_tables[i]._state == EXITS)
				//{//计算在新表中的位置并处理冲突
				//	size_t index = koft(_tables[i]._data)%		newtables.size();
				//	while (newtables[index]._state == EXITS)
				//	{
				//		++index;
				//		if (index == _tables.size())
				//		{
				//			index = 0;
				//		}
				//	}
				//	newtables[index] = _tables[i];
				//}
				//	  
				//}
				//_tables.swap(newtables);

			}
			_tables.swap(newht._tables);

			//二次探测
			size_t start = koft(d) % _tables.size();
			size_t index = start;
			int i = 1;
			while (_tables[index]._state == EXITS)
			{

				if (koft(_tables[index]._data) == koft(d))
				{
					return false;
				}
				index = start + i*i;
				++i;
				
				index %= _tables.size();
			}
			_tables[index]._data = d;
			_tables[index]._state = EXITS;
			_num++;


			//线性探测
			////计算d中的key在表中映射的位置,有冲突则线性探测
			//size_t index = koft(d) % _tables.size();
			//while (_tables[index]._state == EXITS)
			//{

			//	if (koft(_tables[index]._data) == koft(d))
			//	{
			//		return false;
			//	}
			//	++index;
			//	
			//	if (index == _tables.size())
			//	{
			//		index = 0;
			//	}
			//}
			//_tables[index]._data = d;
			//_tables[index]._state = EXITS;
			//_num++;

			return true;
		}
	}
	HashData* Find(const K& key)
	{ 
		KeyOfT koft;
		size_t index = key% _tables.size();
		while (_tables[index]._state != EMPTY)
		{
			if (koft(_tables[index]._data) == key)
			{
				if (_tables[index]._state == EXITS)
				{
				return &tables[index];
				}
				else if (_tables[index]._state == DELETE)
				{
					return nullptr;
				}
				return &_tables[index];
			}
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}

		}
		return nullptr;
	}

	bool Erase(const K&key)
	{
		HashData* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--num;
			return true;
		}
		else
			return false;
	}

private:
	vector<HashData> _tables;
	size_t  _num=0;//存了几个有效数据
};



	void TestHashTable()
	{
		HashTable<int, int, SetKeyOfT<int>>ht;
		ht.Insert(4);
		ht.Insert(14);
		ht.Insert(24);
		ht.Insert(5);
		ht.Insert(15);
		ht.Insert(25);
		ht.Insert(6);
		ht.Insert(16);
	}
}
//开散列
namespace OPEN_HASH
{
template<class T>
struct HashNode
{
	T _data;
	HashNode<T>* _next;
	HashNode(const T& data)
		:_data(data)
		, _next(nullptr)
	{

	}
};

	template<class K, class T, class KeyOfT>
	struct __HashTableIterator
	{
		typedef HashNode<T> Node;
		Node* _node;
	};

	template<class K>
	struct _Hash
	{
		const K&  operator()(const K& key)
		{
			return key;
		}
	};


	struct _HashString
	{
		 size_t  operator()(const string& key)
		{
				 size_t hash = 0;
				 for (size_t i = 0; i < key.size(); ++i)
				 {
					 hash += key[i];
				 }
				 return hash;
		 }
	};


template<class K,class T,class KeyOfT,class Hash=_Hash<K>>
class HashTable 
{
	typedef HashNode<T> Node;

public:
	size_t HashFunc(const K& key)
	{
		
		Hash hash;
		return hash(key);
	}

	bool Insert(const T& data)
	{
		KeyOfT koft;
		//如果负载因子等于1，则增容，避免大量的哈希冲突
		if (_tables.size() == _num)
		{//增容 
			//1、开2倍大小的新表(不一定是2倍)
			//2、遍历旧表的数据，重新计算在新表中的位置
			//3、释放旧表 
			vector <Node*>newtables;
			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			newtables.resize(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				//将旧表中的结点取下来重新计算在新表中的位置，并插入进去
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					size_t index = HashFunc(koft(cur->_data)) % newtables.size();
					cur->_next = newtables[index];
					newtables[index] = cur;
					cur = next; 
				}
				_tables[i] = nullptr;

			}
			_tables.swap(newtables);
		}
		//计算数据在表中映射的位置
		size_t index = HashFunc(koft(data)) % _tables.size();

		//1、先查找要插入的值在不在表中
		Node* cur = _tables[index];
		while (cur)
		{
			if (koft(cur->_data) == koft(data))
				return false;
			else
			{
				cur = cur->_next;
			}
		}
		//2、头插到挂的链表当中（尾插也可以）
		Node* newnode = new Node(data);
		newnode->_next = _tables[index];
		_tables[index] = newnode;
		++_num;
		return true;
	}

	Node* Find(const K& key)
	{
		KeyOfT koft;
		size_t index = HashFunc(key) % _tables.size();
		Node* cur = _tables[index];
		while (cur)
		{
			if (koft(cur->_data) == key)
			{
				return cur;
			}
			else
			{
				cur = cur->_next;
			}
		}
		return nullptr;
	}


	bool Erase(const K& key)
	{
		KeyOfT koft;
		size_t index = HashFunc(key) % _tables.size();
		Node* prev = nullptr;
		Node* cur = _tables[index];
		while (cur)
		{
			if (koft(cur->_data) == key) 
			{
				if (prev == nullptr)
				{
					//表示要删除的是第一个结点
					_tables[index] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}

				
				delete cur;

				return true;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		return false;
	}
	~HashTable()
	{
		Clear();
	}

	void Clear()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			Node* cur = _tables[i];
			while (cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}
			_tables[i] = nullptr;
		}
	}

private:
	vector<Node*> _tables;
	size_t _num=0;//记录表中存储的数据个数


};

void TestHashTable()
{
	HashTable<int, int, SetKeyOfT<int>>ht;
	ht.Insert(4);
	ht.Insert(14);
	ht.Insert(24);
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(25);
	ht.Insert(6);
	ht.Insert(16);
	ht.Insert(26);
	ht.Insert(36);
	ht.Insert(33);

	ht.Erase(4);
	ht.Erase(14);
}

	void TestHashTable2()
	{
		HashTable<string, string, SetKeyOfT<string>, _HashString> ht;
		ht.Insert("sort");
		ht.Insert("string");
		ht.Insert("left");
	}
}