#pragma once
#include<iostream>
#include<vector>
#include<ctime>
//#include"AVLTree.h"
using namespace std;
enum Colour
{
	BLACK,
	RED,
};
template<class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	Colour _col;

	RBTreeNode(const T&data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _col(RED)
	{}
private:
};
template<class T, class Ref, class Ptr >//Ref-->referrence
struct __TreeIterator
{
	typedef RBTreeNode< T> Node;
	typedef __TreeIterator<T, Ref, Ptr> Self;
	Node* _node;


	__TreeIterator(Node *node)
		:_node(node)
	{ 


	}
	Ref &operator*()
	{ 
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		//1������Ҳ�Ϊ�գ��������һ�����Ǿ�����������������	
		//2�������Ϊ�գ���ʾ_node���ڵ������Ѿ�������ɣ���һ���ڵ���������������
		//����·�������Һ�������������Ǹ�����
		if (_node->_right != nullptr)
		{
		
			Node* subleft = _node->_right;
			while (subleft->_left)
			{
				subleft = subleft->_left;

			}
			_node = subleft;
		}
		else//��Ϊ�գ����Һ�������������Ǹ�����
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent&&cur==parent->_right)//parentΪ�����������Ϊ���ڵ��parentΪ��
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}

			_node = parent;
		} 
		return *this;
	}

	Self& operator--()
	{
		return *this;
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}

	bool operator==(const Self& s)
	{
		return _node == s._node;
	}
};
template<class K, class T,class KOfT>
 

class RBTree
{
	typedef RBTreeNode< T> Node;
public:
	typedef __TreeIterator<T,T&,T*> iterator ;
	typedef __TreeIterator<T, const T&,const T*> const_iterator;

	iterator begin()//��Ϊ���������������������壬��˴˴��Ŀ�ʼ��������Ϊ���������ͷ
	{
		Node* cur = _root;
		while (cur&&cur->_left)
		{
			cur=cur->_left;
		}
		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}


	//1/���������Ĺ�����в���
	pair<iterator,bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;
			return make_pair(iterator(_root),true);
		}


		KOfT koft; 
		Node* parent = nullptr;
		Node* cur = _root; 
		while (cur)
		{
			if (koft(cur->_data) <koft(data))
			{
				parent = cur;
				cur = cur->_right;

			}
			else if (koft(cur->_data)> koft(data))
			{
				parent = cur;
				cur = cur->_left;

			}
			else
			{
				return make_pair(iterator(cur), false);
			}
		}
		cur = new Node(data);

		Node* newnode = cur;
		if (koft(parent->_data) < koft(cur->_data))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//�������Ϊ��
		cur->_col = RED;

		while (parent&&parent->_col == RED)
		{
			//����������� �ؼ�������
			Node * grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//���1��uncle������Ϊ��
				if (uncle&& uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//�������ϴ���
					cur = grandfather;
					parent = cur->_parent;
				}
				//���2or���3
				//uncle�����ڻ���uncle������Ϊ��
				else
				{
					//���3��˫��--����Ϊ����
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					//���ڱ�ɵڶ��������ps���п����ǵ����ֱ�����ģ�
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//���1��uncle������Ϊ��
				//���2or���3
				//uncle�����ڻ���uncle������Ϊ��
				if (uncle&& uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;

				}
			}

		}
		_root->_col = BLACK;

		return make_pair(iterator(newnode), true);
	}
	void RotateL(Node* parent)//�ǵ�Ҫ����ÿ������parent
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;


		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;

		}
		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		//1��ԭ��parent��������ĸ�������subR�Ǹ�
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//2��parent�����������ĸ�,����parent�ĸ��ڵ�ȷ��parent���丸�ڵ�����ӻ����Һ��ӣ���������Ӧָ��ָ��subR��subR�ĸ��ڵ�ָ��ppNode
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}

	}
	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;;
		_InOrder(root->_right);

	}

	void InOrder()
	{
		_InOrder(_root);//����������õ�˽�е�_root,���������ʱ�ò��������д����������
		cout << endl;
	}
	void RotateR(Node* parent)//�ǵ�Ҫ����ÿ������parent
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}
		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (parent == ppNode->_right)
			{
				ppNode->_right = subL;

			}
			else
			{
				ppNode->_left = subL;
			}
			subL->_parent = ppNode;
		}

	}
	
	bool IsValidRBTree()
	{
		Node* pRoot = _root;
		// ����Ҳ�Ǻ����
		if (nullptr == pRoot)
			return true;
		// �����ڵ��Ƿ��������
		if (BLACK != pRoot->_col)
		{
			cout << "Υ����������ʶ������ڵ����Ϊ��ɫ" << endl;
			return false;
		}
		// ��ȡ����һ��·���к�ɫ�ڵ�ĸ���
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_col)
				blackCount++;
			pCur = pCur->_left;
		}
		// ����Ƿ��������������ʣ�k������¼·���к�ɫ�ڵ�ĸ���
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//�ߵ�null֮���ж�k��black�Ƿ����
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << endl;
				return false;
			}
			return true;

		}
		// ͳ�ƺ�ɫ�ڵ�ĸ���
		if (BLACK == pRoot->_col)
			k++;
		// ��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_col && RED == pRoot->_col)
		{
			cout << "Υ����������û������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}
		return _IsValidRBTree(pRoot->_left, k, blackCount) &&
			_IsValidRBTree(pRoot->_right, k, blackCount);
	}

	iterator Find(const K& key)
	{
		KOfT koft;
		Node* cur = _root;
		while (cur)
		{

			if (koft(cur->_data )< koft(data))
			{
				cur = cur->_right;
			}
			else if (koft(cur->_data)> koft(data))
			{
				cur = cur->_left;
			}
			else
				return iterator(cur);
		}
		return iterator(nullptr);
	}

private:
	Node* _root = nullptr;
};

//void TestRBTree()
//{
//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	RBTree<int, int>t;
//	for (auto e : a)
//	{
//		t.Insert(make_pair(e, e));
//	}
//	t.InOrder();
//	cout << t.IsValidRBTree() << endl;
//}

//void TestRB_AVLTree()
//{
//	//�������AVL��Ч�ʱȽ�
//	const int n = 100000;
//	vector<int> v;
//	v.reserve(n);
//	srand(time(0));
//	for (size_t i = 0; i < n; ++i)
//	{
//		v.push_back(rand());
//	}
//	RBTree<int, int>rbtree;
//	AVLTree<int, int>avltree;
//
//	size_t begin1 = clock();
//	for (auto e : v)
//	{
//		rbtree.Insert(make_pair(e, e));
//	}
//	size_t end1 = clock();
//
//	size_t begin2 = clock();
//	for (auto e : v)
//	{
//		avltree.Insert(make_pair(e, e));
//	}
//	size_t end2 = clock();
//
//	cout << "rbtree: " << end1 - begin1 << endl;
//	cout << "avltree: " << end2 - begin2 << endl;
//
//}
//
//int main()
//{
//	//TestRBTree();
//	TestRB_AVLTree();
//	return 0;
//}