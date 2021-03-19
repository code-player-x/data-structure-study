#pragma once
#include<iostream>

using namespace std;

template<class K, class V >
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;//balance factor ƽ������

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
		//1.�Ȱ��������Ĺ�����в���
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
		//����ƽ������
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
				//˵��parent���ڵ������ĸ߶�û�䣬(�Ѱ����Ǳ�������)���½���
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//˵��parent���ڵ������ĸ߶ȱ��ˣ��������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)//parent���ڵ��������������ˣ���ת��ƽ����
				//1����תǰ���Ǳ���������������������
				//2����ת��ƽ����
			{
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						//˫��
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
						//˫��
						RotateLR(parent);
					}
				}
				//��ת��ɺ�parent���ڵ��������ĸ߶Ȼָ����˲�����ǰ�ĸ߶�
				//������������Ƕ���һ��û��Ӱ��
				break;
			}
		}
		return true;
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
		parent->_bf = subR->_bf = 0;
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
		_InOrder(_root);//����������õ�˽�е�_root,���������ʱ�ò��������д����������
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

