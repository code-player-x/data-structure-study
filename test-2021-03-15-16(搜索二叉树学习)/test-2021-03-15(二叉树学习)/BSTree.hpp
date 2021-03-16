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
		_InOrder(_root);//����������õ�˽�е�_root,���������ʱ�ò��������д����������
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
			if (cur->_key > key)//keyС�ڵ�ǰ����key����������������
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)//key���ڵ�ǰ����key����������������
			{
				parent = cur;
				cur = cur->_right;
			}
			else//key���ڵ�ǰ����key���жϲ�ͬ���׼��ɾ��
				//1����Ϊ��
				//2����Ϊ��
				//3�����Ҷ���Ϊ��
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
					if (cur == _root)//��������������Ϊ�գ���Ҫɾ�������
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
				
				else//������������Ϊ�յ������
					//�������������ֵ��������������Сֵ���滻�ýڵ��ֵ
				{//ɾ��������ʹ��˫ָ�룬��һ��ָ������¼Ҫɾ�����ĸ���
					Node* rightMinParent = cur;
					Node* rightMin = cur->_right;//������������Сֵ
					while (rightMin->_left)
					{
						rightMinParent = rightMin;
						rightMin = rightMin->_left;
					}
					//���ɾ��
					cur->_key = rightMin->_key;
					//����������������������������������parentָ���������������
					
					//װ����ɾ��rightMin
			
					if (rightMin == rightMinParent->_left)
					{//����������е�һ��������������,��rightMin����Ϊ�գ��ø���ָ��rightMin���ҾͿ���
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

void TestBSTree1()//ֻ��һ��key��ģ��
{
	//BSTree<int> tree1;

	//int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	//for (auto e : a)
	//{
	//	tree1.Insert(e);
	//}
	//tree1.Inorder();

	//tree1.Erase(7);//һ
	//tree1.InOrder();

	////ɾ��Ҷ�ӽ��
	//tree1.Erase(2);
	//tree1.InOrder();
	//
	////��Ϊ�ջ�����Ϊ��
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
void TestBSTree2()//key��valueģ��
{
	////�������������
	//BSTree<string, string>dict;
	//dict.Insert("sort", "����");
	//dict.Insert("string", "�ַ���");
	//dict.Insert("tree", "��");
	//dict.Insert("insert", "����");

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
	//		cout <<"�޴˵���"<< endl;
	//	}
	//}
	//����������ͳ�ƴ���
	string strArr[] = { "����", "ƻ��", "�㽶", "ӣ��", "����", 
		"����", "ƻ��", "����", };

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
