#pragma once
#include<iostream>

using namespace std;
template <class K,class V>
struct BSTreeNode
{
	BSTreeNode<K,V>* _left;
	BSTreeNode<K,V>* _right;
	K _key;
	V _value;


	BSTreeNode(const K& key, const V& value)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
		, _value(value)
	{}
};
template <class K, class V>

class BSTree//Binary Search Tree
{
	typedef BSTreeNode<K,V> Node;

public:
	
	
	bool Insert(const K &key, const V& value)
	{
		if (_root == nullptr)
		{
			_root = new Node(key, value);
			return true;
		}
		Node*parent = nullptr;
		Node* cur = _root;
		while (cur )
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;

			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(key,value);
		if (parent->_key > key)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}

		return true;  
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_key << ":" << root->_value << endl;;
		_InOrder(root->_right);

	}

	void InOrder()
	{
		_InOrder(_root);//在类里可以拿到私有的_root,在类外调用时拿不到，因此写成两个函数
		cout << endl;
	}
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (cur->_key < key)
				cur = cur->_right;
			else if (cur->_key > key)
				cur = cur->_left;
			else
				return cur;
		}
		return nullptr; 
	}

	bool Erase(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		
		while (cur)
		{
			if (cur->_key > key)//key小于当前结点的key，到结点的左子树找
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)//key大于当前结点的key，到结点的右子树找
			{
				parent = cur;
				cur = cur->_right;
			}
			else//key等于当前结点的key，判断不同情况准备删除
				//1、左为空
				//2、右为空
				//3、左右都不为空
			{
				if (cur->_left == nullptr)
				{
					if (cur == _root)
					{
						_root = cur->_right;
					}
					else
					{
						if (parent->_right == cur)
							parent->_right = cur->_right;
						if (parent->_left == cur)
							parent->_left = cur->_right;
					}
					
					delete cur;
				}
				else if (cur->_right == nullptr)
				{
					if (cur == _root)//整个数的右子树为空，且要删除根结点
					{
						_root = cur->_left;
					}
					else
					{
						if (parent->_right == cur)
							parent->_right = cur->_left;
						if (parent->_left == cur)
							parent->_left = cur->_left;
					}
					delete cur;
				}
				
				else//左右子树都不为空的情况，
					//找左子树的最大值或是右子树的最小值来替换该节点的值
				{//删除结点必须使用双指针，用一个指针来记录要删除结点的父亲
					Node* rightMinParent = cur;
					Node* rightMin = cur->_right;//到右子树找最小值
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}
					//替代删除
					cur->_key = rightMin->_key;
					//如果右子树最左结点有右子树，让最左结点的parent指向最左结点的右子树
					
					//装换成删除rightMin
			
					if (rightMin == rightMinParent->_left)
					{//如果右子树中第一个结点就是最左结点,即rightMin是左为空，让父亲指向rightMin的右就可以
						rightMinParent->_left = rightMin->_right;
					}
					else
					rightMinParent->_right = rightMin->_right;

					delete rightMin;

				}
				return true;
			}
			
		}
		return false;
	}

private:
	Node* _root=nullptr;
};

void TestBSTree1()//只有一个key的模型
{
	//BSTree<int> tree1;

	//int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	//for (auto e : a)
	//{
	//	tree1.Insert(e);
	//}
	//tree1.Inorder();

	//tree1.Erase(7);//一
	//tree1.InOrder();

	////删除叶子结点
	//tree1.Erase(2);
	//tree1.InOrder();
	//
	////左为空或者右为空
	//tree1.Erase(8);
	//tree1.Erase(1);
	//tree1.InOrder();

	//tree1.Erase(5);
	//tree1.InOrder();

	//for (auto e : a)
	//{
	//	tree1.Erase(e);
	//	tree1.Inorder();
	//}
	
}
void TestBSTree2()//key，value模型
{
	////二叉搜索树查词
	//BSTree<string, string>dict;
	//dict.Insert("sort", "排序");
	//dict.Insert("string", "字符串");
	//dict.Insert("tree", "树");
	//dict.Insert("insert", "插入");

	//string str;
	//while (cin >> str)
	//{
	//	BSTreeNode<string, string> *ret = dict.Find(str);
	//	if (ret)
	//	{
	//		cout << ret->_value << endl;
	//	}
	//	else
	//	{
	//		cout <<"无此单词"<< endl;
	//	}
	//}
	//二叉搜索树统计次数
	string strArr[] = { "西瓜", "苹果", "香蕉", "樱桃", "西瓜", 
		"西瓜", "苹果", "西瓜", };

	BSTree<string, int> countTree;
	for (auto str : strArr)
	{
		BSTreeNode<string, int>*ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}

	}
	countTree.InOrder();
}
