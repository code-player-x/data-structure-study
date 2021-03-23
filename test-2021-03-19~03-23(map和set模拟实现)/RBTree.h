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
		//1、如果右不为空，中序的下一个就是就是右子树的最左结点	
		//2、如果右为空，表示_node所在的子树已经访问完成，下一个节点在他的祖先中找
		//沿着路径往上找孩子是它的左的那个祖先
		if (_node->_right != nullptr)
		{
		
			Node* subleft = _node->_right;
			while (subleft->_left)
			{
				subleft = subleft->_left;

			}
			_node = subleft;
		}
		else//右为空，找找孩子是它的左的那个祖先
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			while (parent&&cur==parent->_right)//parent为空则截至，因为根节点的parent为空
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

	iterator begin()//因为红黑树的中序遍历最有意义，因此此处的开始迭代器设为中序遍历的头
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


	//1/按搜索树的规则进行插入
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
		//新增结点为红
		cur->_col = RED;

		while (parent&&parent->_col == RED)
		{
			//红黑树的条件 关键看叔叔
			Node * grandfather = parent->_parent;
			if (grandfather->_left == parent)
			{
				Node* uncle = grandfather->_right;
				//情况1：uncle存在且为红
				if (uncle&& uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;
					//继续往上处理
					cur = grandfather;
					parent = cur->_parent;
				}
				//情况2or情况3
				//uncle不存在或者uncle存在且为黑
				else
				{
					//情况3：双旋--》变为单旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					//现在变成第二种情况（ps：有可能是第三种变过来的）
					RotateR(grandfather);
					grandfather->_col = RED;
					parent->_col = BLACK;
				}
			}
			else
			{
				Node* uncle = grandfather->_left;
				//情况1：uncle存在且为红
				//情况2or情况3
				//uncle不存在或者uncle存在且为黑
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
	void RotateL(Node* parent)//记得要处理每个结点的parent
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

		//1、原来parent是这棵树的根，现在subR是根
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		//2、parent不是整棵树的根,访问parent的父节点确定parent是其父节点的左孩子还是右孩子，并令其相应指针指向subR，subR的父节点指向ppNode
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
		_InOrder(_root);//在类里可以拿到私有的_root,在类外调用时拿不到，因此写成两个函数
		cout << endl;
	}
	void RotateR(Node* parent)//记得要处理每个结点的parent
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
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;
		// 检测根节点是否满足情况
		if (BLACK != pRoot->_col)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}
		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_col)
				blackCount++;
			pCur = pCur->_left;
		}
		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;

		}
		// 统计黑色节点的个数
		if (BLACK == pRoot->_col)
			k++;
		// 检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_col && RED == pRoot->_col)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
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
//	//红黑树与AVL树效率比较
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