#include<iostream>
#include<assert.h>
using namespace std;
namespace px
{

	template<class T>
	class vector{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}
		const_iterator begin()const
		{
			return _start;
		}

		const_iterator end()const
		{
			return _finish;
		}
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T * tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T)*sz);
					delete[] _start;
				}

				_start = tmp;
				_finish = tmp + sz;
				_endofstorage = tmp + n;
			}

		}
		void push_back(const T& x)
		{
			//if (_finish == _endofstorage)
			//{
			//	size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
			//	reserve(newcapacity);
			//}
			//*_finish = x;
			//++_finish;
			insert(_finish, x);
		}
		void pop_back()
		{
			/*assert(_start < _finish);
			--_finish;*/
			erase(_finish - 1);
		}
		size_t size()
		{
			return _finish - _start;
		}
		void resize(size_t n,T& val=T())//给个T类型的缺省值
		{
			if (n < size())
			{
				_endofstorage = n;
				_finish =_start[n];
			}
			else
			{
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
				_endofstorage = _start + newcapacity;

			}
		}




		T & operator[](size_t i)
		{
			assert(i < size());
			return _start[i];
		}

		size_t capacity()
		{
			return _endofstorage - _start;
		}
	
		
		void insert(iterator pos, const T& x)
		{ 
			assert(pos <= _finish);
			if (_finish == _endofstorage)//空间不够则扩容
			{
				size_t n = pos - _start;//防止因扩容导致迭代器失效
				size_t newcapacity = capacity() == 0 ? 2 : capacity() * 2;
				reserve(newcapacity);
				//如果增容原来的pos就失效了，这里需要重新计算位置
				pos = _start + n;//防止因扩容导致迭代器失效
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end+1) = *end;
				--end;
			}
			*pos =x;
			++_finish;

		}
		iterator erase(iterator pos)
		{
			assert(pos <_finish);//不能等于_finish
			iterator it = pos;
			while (it <_finish)
			{
				*(it) = *(it+1);
				++it;
			}
			--_finish;
			return pos;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endofstorage;

	};
	void print_vector(const vector<int>&v)
	{
		vector<int>::const_iterator it = v.begin();
		while (it != v.end())
		{
			//*it += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}
	void test_vector1()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(2);
		v.push_back(2);
		cout << v.size() << endl;
		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			*it += 1;
			cout << *it << " ";
			++it;
		}
		cout << endl;

		for (auto &e : v)//要支持范围for必须是标准的迭代器，有begin，end，和finish
		{
			e -= 1;
			cout << e << " ";
		}
		cout << endl;

		for (size_t i = 0; i < v.size(); ++i)
		{
			cout << v[i] <<" ";
		}
		cout << endl;
		print_vector(v);
	}
	void test_vector2()
	{
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);
		v.push_back(6);
		v.push_back(7);
		v.push_back(8);


		v.insert(v.begin(), 0);
		print_vector(v);

		vector<int>::iterator it = v.begin();
		while (it != v.end())
		{
			if (*it % 2 == 0)
			{
				it = v.erase(it);
			}
			else
				++it;
		}
		print_vector(v);
		v.pop_back();
		print_vector(v);

	}


}
int main()
{
	//px::test_vector1();
	px::test_vector2();
	return 0;
}