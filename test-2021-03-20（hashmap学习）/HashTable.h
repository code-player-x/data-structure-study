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
	EMPTY,//��
	EXITS,//����
	DELETE,//ɾ��
};
template<class T>
struct HashData
{
	T _data;
	State _state;//״̬����ʾ��λ���ǿգ�����ɾ����Ϊ��
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
		//��������=�������ݸ���/��Ĵ�С  ������ϣ�����ĳ̶�
		//��ӽ�������������Խ���׳�ͻ����ͻԽ�࣬Ч��Խ��
		//��ϣ���������˲����ݣ����Ŷ�ַ����,һ�㸺�����ӵ���0.7���ҾͿ�ʼ����
		//��������ԽС����ͻ����Խ�ͣ�����Ч��Խ�ߣ����Ǹ�������ԽС���˷ѵĿռ�Խ��
		//���Ը�������һ��ȡһ������ֵ
		KeyOfT koft;

		if (_tables.size() == 0 || _num * 10 / _tables.size() >= 7)
		{
			//���� 
			//1����2����С���±�
			//2�������ɱ�����ݣ����¼������±��е�λ��
			//3���ͷžɱ� 
			//vector<HashData>newtables;
			HashTable<K, T, KeyOfT>newht;
			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			newht._tables.resize(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{	//��˼·
				if (_tables[i]._state == EXITS)
				{
					newht.Insert(_tables[i]._data);
				}

				//if (_tables[i]._state == EXITS)
				//{//�������±��е�λ�ò������ͻ
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

			//����̽��
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


			//����̽��
			////����d�е�key�ڱ���ӳ���λ��,�г�ͻ������̽��
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
	size_t  _num=0;//���˼�����Ч����
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
//��ɢ��
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
		//����������ӵ���1�������ݣ���������Ĺ�ϣ��ͻ
		if (_tables.size() == _num)
		{//���� 
			//1����2����С���±�(��һ����2��)
			//2�������ɱ�����ݣ����¼������±��е�λ��
			//3���ͷžɱ� 
			vector <Node*>newtables;
			size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			newtables.resize(newsize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				//���ɱ��еĽ��ȡ�������¼������±��е�λ�ã��������ȥ
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
		//���������ڱ���ӳ���λ��
		size_t index = HashFunc(koft(data)) % _tables.size();

		//1���Ȳ���Ҫ�����ֵ�ڲ��ڱ���
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
		//2��ͷ�嵽�ҵ������У�β��Ҳ���ԣ�
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
					//��ʾҪɾ�����ǵ�һ�����
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
	size_t _num=0;//��¼���д洢�����ݸ���


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