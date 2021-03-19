#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
#include<cstring>
#include<assert.h>
using namespace std;
//namespace px//创建一个自己的命名空间
//{
//	//面试题 ：实现一个简单的string->深浅拷贝问题
//	class string
//	{
//	public:
//		//string()
//		//	:_str(new char[1])
//		//{
//		//	_str[0] = '\0';
//		//}
//		//string( char* str)
//		//	:_str(new char[strlen(str) + 1])//+1是为了\0
//		//{
//		//	strcpy_s(_str, strlen(str) + 1,str);
//
//		//}
//		//合二为一全缺省
//		string( char* str="")
//			:_str(new char[strlen(str) + 1])//+1是为了\0
//		{
//			strcpy_s(_str, strlen(str) + 1,str);
//
//		}
//		~string()
//		{
//			delete[]_str;
//			_str = nullptr;
//		}
//		//实现深拷贝
//		string(const string &s)
//			:_str(new char[strlen(s._str)+1])//开空间
//		{
//			strcpy_s(_str, strlen(s._str) + 1, s._str);//拷数据
//		}
//		size_t size()
//		{
//			return strlen(_str);
//		}
//
//		char& operator[](size_t i)
//		{
//			return _str[i];
//		}
//
//		const char* c_str()
//		{
//			return this->_str;
//		}
//		//operator=的实现s1=s3
//		//s1=s1防止这种情况出现
//		string&  operator=(const string &s)
//		{
//			if (this != &s)
//			{
//				char * tmp = new char[strlen(s._str) + 1];//开空间
//				strcpy_s(tmp, strlen(s._str) + 1, s._str);//拷数据
//				delete[] _str;//释放右空间
//				_str = tmp;
//			}
//			return *this;
//
//		}
//	private:
//		char* _str;
//	};
//	void test_string1()
//	{
//		string s1("hello");
//		string s2;
//
//		for (size_t i = 0; i < s1.size(); ++i)
//		{
//			s1[i] += 1;
//			cout << s1[i] << " ";
//		}
//		cout << endl;
//
//		for (size_t i = 0; i < s2.size(); ++i)
//		{
//			s2[i] += 1;
//			cout << s2[i] << " ";
//		}
//		cout << endl;
//	}
//	void test_string2()
//	{
//		string s1("hello");
//		string s2(s1);
//		string s3("world");
//		 s1 = s3;
//		cout << s1.c_str()<<endl;
//		cout << s3.c_str() << endl;
//	}
//
//}

namespace px
{//实现一个支持增删查改的string
	class string
	{
	public:
		typedef char* iterator;

		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}
		string(const char* str="")
		{
			_size = strlen(str);
			_capacity = _size;//_capacity是有效字符的个数，不包括'\0'
			_str = new char[_capacity + 1];//开空间要给'\0'额外开一个空间
			strcpy_s(_str, strlen(str)+1,str);

		}
		//拷贝构造和赋值作为作业
		//string s2(s1)
		string(const string &s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);
			this->swap(tmp);
		}
		void swap(string &s)
		{
			::swap(_str, s._str);//加个域作用限定符，调全局域的swap
			::swap(_size, s._size);
			::swap(_capacity, s._capacity);
		}
		string& operator=(string s)
		{
			this->swap(s);
			return *this;
		}
		~string()
		{
			delete[]_str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		size_t size() const
		{
			return this->_size;
		}

		size_t capacity()const
		{
			return this->_capacity;
		}
		//operator=

		string operator=(const char* str)
		{
			char* tmp = new char[strlen(str) + 1];
			strcpy_s(_str, strlen(str) + 1, str);
			delete _str;
			_str = tmp;
			return _str;
		}
		char& operator[](size_t i)
		{
			assert(i < _size);
			return this->_str[i];
		}

		const char& operator[](size_t i)const
		{
			assert(i < _size);
			return this->_str[i];
		}

		const char*c_str()
		{
			return _str;
		}
		void reserve(size_t n)//增容
		{
			if (n>_capacity)
			{
				char* tmp = new char[n + 1];
				strcpy_s(tmp, strlen(_str) + 1, _str);
				delete[]_str;
				_str = tmp;
				_capacity = n;
			}
		}
		//增
		void push_back(char ch)
		{
			//空间满了则进行增容
			//if (_size == _capacity)
			//{
			//	size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
			//	//char* tmp= new char[newcapacity + 1];
			//	//strcpy_s(tmp, strlen(_str) + 1, _str);
			//	//delete[]_str;
			//	//_str = tmp;
			//	//_capacity = newcapacity;
			//	reserve(newcapacity);

			//}
			//_str[_size] = ch;
			//++_size;
			//_str[_size] = '\0';
			insert(_size, ch);
		}


		void append(const char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)//空间满了则进行增容
			{//注意这里不能按2倍增，因为不一定够
				size_t newcapacity = _size + len;
				/*char* newstr = new char[newcapacity + 1];
				strcpy_s(newstr, strlen(str) + 1, str);
				delete[]_str;
				_str = newstr;
				_capacity = newcapacity;*/
				reserve(_size + len);
			}
			strcpy_s(_str+_size, strlen(str) + 1, str);
			_size += len;
		}
		//s1+='a'
		string & operator+=(char ch)
		{
			this->push_back(ch);
			return *this;
		}
		//s1+="aaaaaa"
		string & operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}

		string& insert(size_t pos, char ch)
		{
			assert(pos < _size);
			//检查容量，不够则增容
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newcapacity);

			}
			int end = _size;
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
			//_str[_size] = '\0';
			return *this;
		}

		string& insert(size_t pos, const char* str)
		{
			assert(pos<=_size);
			//1.空间满了则进行增容
			size_t len = strlen(str);
			if (_size + len > _capacity)//空间满了则进行增容
			{//注意这里不能按2倍增，因为不一定够
				size_t newcapacity = _size + len;
				/*char* newstr = new char[newcapacity + 1];
				strcpy_s(newstr, strlen(str) + 1, str);
				delete[]_str;
				_str = newstr;
				_capacity = newcapacity;*/
				reserve(_size + len);
			}

			int end = _size;
			while (end >=(int) pos )//int 和unsigned int 会发生隐士类型转换，在0处插入时会有问题
			{
				_str[end + len] = _str[end];
				--end;
				
			}
			//for (size_t i = 0; i < len; ++i)
			//{
			//	_str[pos++] = str[i];
			//}
			
			strncpy_s(_str + pos,sizeof(_str),str, strlen(str));
			_size += len;
			//_str[_size] = '\0';

			return *this;
		}

		void erase (size_t pos,size_t len =npos)//默认为删完
		{
			assert(pos < _size);
			if (len >= _size - pos)//删不完pos后面的字符的情况
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else//会删完pos后面的字符的情况
			{
				size_t i = pos + len;
				while (i<=_size)
				{
					_str[i - len] = _str[i];
					++i;
				}
				_size -= len;
			}
		}

		void resize(size_t n,char ch ='\0')
		{
			if (n < _size)//要resize的空间小于原有字符串长度
			{
				_str[n] = '\0';
				_size = n;
			}
			else 
			{
				if (n>_capacity)//要resize的空间大于原有字符串空间，大于部分初始化为\0
				{
					reserve(n);
				}
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';
			}
		}
		size_t find(char ch, size_t pos = 0)
		{
			for (size_t i = pos; i < _size; ++i)
			{
				if (_str[i] == ch)
					return i;
				
			}
 				return npos; 
		 }
		size_t find(const char* str, size_t pos = 0)
		{
			char* p = strstr(_str, str);
			if (p == nullptr)
			{
				return npos;
			}
			else
			{

				return p - _str;
			}

		}
		//s1<s2
		bool operator<(const string &s)
		{
			int ret = strcmp(_str, s._str);
			return ret < 0;

		}
		bool operator <=(const string &s)
		{
			return *this < s || *this == s;
		}

		bool operator==(const string &s)
		{
			int ret = strcmp(_str, s._str);
			return ret == 0;
		}
		bool operator!=(const string &s)
		{
			return !(*this == s);
		}
		bool operator>(const string &s)
		{
			return !(*this <= s);
		} 
		bool operator>=(const string &s)
		{
			return !(*this < s);
		}


	private:
		char* _str; 
		size_t _size;//已经有多少个有效字符  '\0'不是有效字符
		size_t _capacity;//能存多少个有效字符，至少比_size>1，因为要存"\0"
		static size_t npos;
	};

	size_t string::npos = -1;
	istream& operator>>(istream& in, string&s)
	{
		while (1)
		{
			char ch;
			//in >> ch;
			ch = in.get();
			if (ch == ' ' || ch == '\n')//去掉ch == ' '就是getline
			{
				break;
			}
			else
				s += ch;

		}
		return in;
	}
	ostream& operator<<(ostream& out, const string&s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			cout << s[i];
		}
		return out;
	}
	void test_string1()
	{
		string s1;
		string s2("hello");
		//s1 = s2;
		
		//for (int i = 0; i < s1.size(); ++i)
		//{
		//	cout << s1[i] << endl;
		//}
		cout << s1 << endl;
		cout << s2<< endl;
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		//三种遍历方式
		for (size_t i = 0; i < s2.size(); ++i)
		{
			s2[i] += 1;
			cout << s2[i] << " ";
		}
		cout << endl;
		string::iterator it2 = s2.begin();
		while (it2 != s2.end())
		{
			*it2 -= 1;
			cout << *it2 << " ";
			++it2;
		}
		cout << endl;
		////范围for是由迭代器支持的，也就是说这段代码最终会被编译器替换成迭代器
		for (auto e : s2)
		{
			cout << e << " ";
		}
		cout << endl;

	}
	void test_string2()
	{
		string s1("hello");
		s1.push_back(' ');
		cout << s1 << endl;
		s1.append("world");
		cout << s1 << endl;

		string s3("hello");
		s3 += ' ';//底层调push_back
		s3 += "how are you";//底层调append
		cout << s3 << endl;
	}
	void test_string3()
	{
		string s1("hell o");
		s1.insert(1, 'x');
		s1.insert(1, "xyz");
		//cout << s1<<endl;
		
		string s2("hello");
		s2.reserve(10); 
		cout << s2 << endl; 
		cout << s2.size() << endl;
		cout << s2.capacity() << endl << endl;

		s2.resize(8, 'x');
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl << endl;

		s2.resize(18, 'a');
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;

		s2.resize(2);
		cout << s2 << endl;
		cout << s2.size() << endl;
		cout << s2.capacity() << endl;
	}

	void test_string4()
	{
		string s1("helloworld"); 
		s1.erase(5,2);
		cout << s1 << endl;

		s1.erase(5, 4); 
		cout << s1 << endl;

		string s2("abcdabcdef");
		cout << s2.find("cde") << endl; 
		cout << s2.find("cdex") << endl;
		
	}
	void test_string5()
	{
		string s; 
		cin >> s;
		cout << s;

		char c1, c2, c3;
	}
}
namespace bit_copy
{	// C++的一个常见面试题是让你实现一个String类:
	//限于时间，不可能要求具备std: :string 的功能，但至少要求能正确管理资源。
	//->构造+析构+拷贝+operator=

	class string
	{
	public:
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
		{
			strcpy_s(_str,strlen(str)+1, str);
		}
		//string s2(s1)

		//深拷贝--传统写法
		//string(const string &s)
		//	:_str(new char[strlen(s._str)+1]) //开个一样大的空间，自己拷数据
		//{
		//	strcpy_s(_str, strlen(s._str) + 1, s._str);
		//}
		//深拷贝--现代写法----更简洁
		string(const string &s)
			:_str(nullptr)//初始化—_str为空指针
		{
			string tmp(s._str);//调用构造函数开空间拷数据
			swap(_str, tmp._str);//空手套白狼
		}



		//赋值 ----传统写法
		//string& operator=(const string&s)
		//{
		//	if (this !=& s)
		//	{
		//		char *tmp = new char[strlen(s._str) + 1];
		//		strcpy_s(tmp, strlen(s._str) + 1, s._str);
		//		delete[] _str;
		//		_str = tmp;
		//	}
		//	return *this;
		//}

		//现代写法1
		//string& operator=(const string&s)
		//{
		//	if (this != &s)
		//	{
		//		string tmp(s);//调用拷贝构造函数开空间拷数据
		//		swap(_str,tmp._str);

		//	}
		//	return *this;
		//}

		//现代写法2--这里最巧的就是传值操作--调用一次拷贝构造然后swap
		string& operator=( string s)//s是临时对象，出了作用域就销毁了
		{
			swap(_str, s._str);
			return *this;
		}
		size_t size()
		{
			return strlen(_str);
		}

		char& operator[](size_t i)
		{
			return _str[i];
		}
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
	private: 
		char*_str;


	}; 
	void test_string1()
	{
		string s1("hello");
		string s2(s1);
		for (size_t i=0; i < s2.size(); ++i)
		{
			cout << s2[i] << " ";
		}
		cout << endl;
		string s3("world");
		s1 = s3;
		for (size_t i=0; i < s1.size(); ++i)
		{
			cout << s1[i] << " ";
		}
		cout << endl;
	}
}