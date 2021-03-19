#pragma once
#include<iostream>

using namespace std;

template<class K, class V >
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;//balance factor 平衡因子

	pair<K, V> _kv;

	AVLTreeNode(const pair<K, V>&kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}

};

template<class K, class V >
class AVLTree
{
public:
	typedef AVLTreeNode<K, V> Node;

	bool Insert(const pair<K, V>&kv)
	{
		//1.先按搜索树的规则进行插入
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;

			}
			else if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;

			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//更新平衡因子
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;

			}
			if (parent->_bf == 0)
			{
				//说明parent所在的子树的高度没变，(把矮的那边填上了)更新结束
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//说明parent所在的子树的高度变了，继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//parent所在的子树出现问题了，旋转成平衡树
				//1、旋转前提是保持它依旧是搜索二叉树
				//2、旋转成平衡树
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						//双旋
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						//双旋
						RotateLR(parent);
					}
				}
				//旋转完成后，parent所在的整棵树的高度恢复到了插入结点前的高度
				//如果是子树，那对上一层没有影响
				break;
			}
		}
		return true;
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
		parent->_bf = subR->_bf = 0;
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
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
		subL->_bf = parent->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);

		if (bf == -1)
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
			subRL->_bf = 0;
		}
		else if (bf == 0)
		{
			subR->_bf = 0;
			parent->_bf = 0;
			subRL->_bf = 0;
		}
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);
		if (bf == 1)
		{
			subL->_bf = -1;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else if (bf == 0)
		{
			subL->_bf = 0;
			parent->_bf = 0;
			subLR->_bf = 0;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);

	}

	void InOrder()
	{
		_InOrder(_root);//在类里可以拿到私有的_root,在类外调用时拿不到，因此写成两个函数
		cout << endl;
	}
private:
	Node* _root = nullptr;

};

void test()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	AVLTree<int, int>t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}
	t.InOrder();

}

