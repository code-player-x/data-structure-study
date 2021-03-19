#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
#include<cstring>
#include<assert.h>
using namespace std;
//namespace px//����һ���Լ��������ռ�
//{
//	//������ ��ʵ��һ���򵥵�string->��ǳ��������
//	class string
//	{
//	public:
//		//string()
//		//	:_str(new char[1])
//		//{
//		//	_str[0] = '\0';
//		//}
//		//string( char* str)
//		//	:_str(new char[strlen(str) + 1])//+1��Ϊ��\0
//		//{
//		//	strcpy_s(_str, strlen(str) + 1,str);
//
//		//}
//		//�϶�Ϊһȫȱʡ
//		string( char* str="")
//			:_str(new char[strlen(str) + 1])//+1��Ϊ��\0
//		{
//			strcpy_s(_str, strlen(str) + 1,str);
//
//		}
//		~string()
//		{
//			delete[]_str;
//			_str = nullptr;
//		}
//		//ʵ�����
//		string(const string &s)
//			:_str(new char[strlen(s._str)+1])//���ռ�
//		{
//			strcpy_s(_str, strlen(s._str) + 1, s._str);//������
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
//		//operator=��ʵ��s1=s3
//		//s1=s1��ֹ�����������
//		string&  operator=(const string &s)
//		{
//			if (this != &s)
//			{
//				char * tmp = new char[strlen(s._str) + 1];//���ռ�
//				strcpy_s(tmp, strlen(s._str) + 1, s._str);//������
//				delete[] _str;//�ͷ��ҿռ�
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
{//ʵ��һ��֧����ɾ��ĵ�string
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
			_capacity = _size;//_capacity����Ч�ַ��ĸ�����������'\0'
			_str = new char[_capacity + 1];//���ռ�Ҫ��'\0'���⿪һ���ռ�
			strcpy_s(_str, strlen(str)+1,str);

		}
		//��������͸�ֵ��Ϊ��ҵ
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
			::swap(_str, s._str);//�Ӹ��������޶�������ȫ�����swap
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
		void reserve(size_t n)//����
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
		//��
		void push_back(char ch)
		{
			//�ռ��������������
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
			if (_size + len > _capacity)//�ռ��������������
			{//ע�����ﲻ�ܰ�2��������Ϊ��һ����
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
			//�������������������
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
			//1.�ռ��������������
			size_t len = strlen(str);
			if (_size + len > _capacity)//�ռ��������������
			{//ע�����ﲻ�ܰ�2��������Ϊ��һ����
				size_t newcapacity = _size + len;
				/*char* newstr = new char[newcapacity + 1];
				strcpy_s(newstr, strlen(str) + 1, str);
				delete[]_str;
				_str = newstr;
				_capacity = newcapacity;*/
				reserve(_size + len);
			}

			int end = _size;
			while (end >=(int) pos )//int ��unsigned int �ᷢ����ʿ����ת������0������ʱ��������
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

		void erase (size_t pos,size_t len =npos)//Ĭ��Ϊɾ��
		{
			assert(pos < _size);
			if (len >= _size - pos)//ɾ����pos������ַ������
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else//��ɾ��pos������ַ������
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
			if (n < _size)//Ҫresize�Ŀռ�С��ԭ���ַ�������
			{
				_str[n] = '\0';
				_size = n;
			}
			else 
			{
				if (n>_capacity)//Ҫresize�Ŀռ����ԭ���ַ����ռ䣬���ڲ��ֳ�ʼ��Ϊ\0
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
		size_t _size;//�Ѿ��ж��ٸ���Ч�ַ�  '\0'������Ч�ַ�
		size_t _capacity;//�ܴ���ٸ���Ч�ַ������ٱ�_size>1����ΪҪ��"\0"
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
			if (ch == ' ' || ch == '\n')//ȥ��ch == ' '����getline
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
		//���ֱ�����ʽ
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
		////��Χfor���ɵ�����֧�ֵģ�Ҳ����˵��δ������ջᱻ�������滻�ɵ�����
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
		s3 += ' ';//�ײ��push_back
		s3 += "how are you";//�ײ��append
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
{	// C++��һ������������������ʵ��һ��String��:
	//����ʱ�䣬������Ҫ��߱�std: :string �Ĺ��ܣ�������Ҫ������ȷ������Դ��
	//->����+����+����+operator=

	class string
	{
	public:
		string(const char* str = "")
			:_str(new char[strlen(str)+1])
		{
			strcpy_s(_str,strlen(str)+1, str);
		}
		//string s2(s1)

		//���--��ͳд��
		//string(const string &s)
		//	:_str(new char[strlen(s._str)+1]) //����һ����Ŀռ䣬�Լ�������
		//{
		//	strcpy_s(_str, strlen(s._str) + 1, s._str);
		//}
		//���--�ִ�д��----�����
		string(const string &s)
			:_str(nullptr)//��ʼ����_strΪ��ָ��
		{
			string tmp(s._str);//���ù��캯�����ռ俽����
			swap(_str, tmp._str);//�����װ���
		}



		//��ֵ ----��ͳд��
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

		//�ִ�д��1
		//string& operator=(const string&s)
		//{
		//	if (this != &s)
		//	{
		//		string tmp(s);//���ÿ������캯�����ռ俽����
		//		swap(_str,tmp._str);

		//	}
		//	return *this;
		//}

		//�ִ�д��2--�������ɵľ��Ǵ�ֵ����--����һ�ο�������Ȼ��swap
		string& operator=( string s)//s����ʱ���󣬳����������������
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