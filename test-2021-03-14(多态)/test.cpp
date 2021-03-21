#include<iostream>
using namespace std;

//多态的两个条件
//1、虚函数的重写
//2、父类对象的指针或者引用去调用虚函数

// 满足多态：跟指向对象的类型无关，指向哪个对象调用就是他的虚函数
//不满足多态：跟调用对象的类型有关，类型是什么调用的就是谁的虚函数
 
//class Person 
//{
//public:
//	virtual void BuyTicket() { cout << "买票-全价" << endl; }
//};
//class Student : public Person
//{
//public:
//	virtual void BuyTicket() { cout << "买票-半价" << endl; }
//	/*注意：在重写基类虚函数时，派生类的虚函数在不加virtual关键字时，虽然也可以构成重写(因为继
//	承后基类的虚函数被继承下来了在派生类依旧保持虚函数属性),但是该种写法不是很规范，不建议这样使用
//	*/
//	/*void BuyTicket() { cout << "买票-半价" << endl; }*/
//};
//void Func(Person& p)
//{
//	p.BuyTicket();
//}
//
//	
//int main()
//{
//	Person ps;
//	Student st;
//	Func(ps);
//	Func(st);
//	return 0;
//}


//class Person {
//public:
//	virtual ~Person() 
//	{ cout << "Person::~Person()" << endl; }
//	//析构函数的函数名会被处理成destructor
//};
//
//class Student : public Person {
//public:
//	virtual ~Student() { cout << "Student::~Student()" << endl; }
	//析构函数的函数名会被处理成destructor
	//override 检查子类的虚函数是否重写了父类的虚函数
//};
// 只有派生类Student的析构函数重写了Person的析构函数，下面的delete对象调用析构函数，才能
//构成多态，才能保证p1和p2指向的对象正确的调用析构函数。
//int main()
//{
//	//Person p;
//	//Student s;
//	Person* p1 = new Person;
//	delete p1;
//
//	Person* p2 = new Student;
//	delete p2;
//	return 0;
//}

//抽象类
//class Car
//{
//public:
//	virtual void Drive() = 0;//纯虚函数 不需要实现
//};
////纯虚函数的作用
////1、强制子类去完成重写
////2、表示抽象的类型。抽象就是在现实中没有对应的实体的
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-舒适" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-操控" << endl;
//	}
//};
//void Test()
//{
//	Car* pBenz = new Benz;//父类指针指向子类对象
//	pBenz->Drive();
//	Car* pBMW = new BMW;
//	pBMW->Drive();
//}
//
//int main()
//{
//	//Car car;//抽象类不能实例化出对象
//	Test();
//	return 0;
//} 

//class Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Base::Func1()" << endl;
//	}
//	virtual void Func2()
//	{
//		cout << "Base::Func2()" << endl;
//	}
//	void Func3() 
//	{
//		cout << "Base::Func3()" << endl;
//	}
//private:
//	int _b = 1;
//};
//class Derive : public Base
//{
//public:
//	virtual void Func1()
//	{
//		cout << "Derive::Func1()" << endl;
//	}
//private:
//	int _d = 2;
//};
//
//void test1()
//{	//取出对象的前4个字节
//	Base b1;
//	printf("vfptr:%p\n", *(int*)&b1);
//	 
//	int i = 0;
//	int* p1 = &i;
//	int* p2 = new int;
//	char* p3 = "hello";
//	printf("栈变量:%p\n", p1);
//	printf("堆变量:%p\n", p2);
//	printf("代码段变量:%p\n", p3);
//	printf("代码段函数地址:%p\n", &Base::Func3);
//	printf("代码段虚函数地址:%p\n", &Base::Func1);
//}
//
//int main()
//{
//	//Base b;
//	//Derive d;
//	//test1();
//	int i = 0;
//	double d = 1.1;
//	//静态绑定静态的多态(静态:编译时确定函数地址)
//
//	//动态绑定动态的多态(动态:运行时到虚表中找虚函数地址>
//	Base* p = new Base;
//	p->Func1();
//	p = new Derive; p->Func1();
//	return 0;
//	
//}


//class Base {
//public:
//	virtual void func1() { cout << "Base::func1" << endl; }
//	virtual void func2() { cout << "Base::func2" << endl; }
//private:
//	int a;
//};
//class Derive :public Base {
//public:
//	virtual void func1() { cout << "Derive::func1" << endl; }
//	virtual void func3() { cout << "Derive::func3" << endl; }
//	virtual void func4() { cout << "Derive::func4" << endl; }
//private:
//	int b;
//};
//
////void(*p)();//定义一个函数指针变量
//typedef void(*VF_PTR)();//函数指针类型typedef
//void printVFTable(VF_PTR* pTable)//打印单继承子类对象中内存监视里无法查看的func3和cunc4
//{
//	for (size_t i = 0; pTable[i] != 0; ++i)
//	{
//		printf("vfTable[%d]:%p",i,pTable[i]);
//		VF_PTR f = pTable[i];
//		f();
//	}
//
//
//	 
//}
//int main()
//{
// 
//	Base b;
//	Derive d; 
//	printVFTable((VF_PTR*)(*(int*)&b));
//	cout << endl;
//	printVFTable((VF_PTR*)(*(int*)&d));
//
//	return 0;
//}

class Base1 {
public:
	virtual void func1() { cout << "Base1::func1" << endl; }
	virtual void func2() { cout << "Base1::func2" << endl; }
private:
	int b1;
};//8字节
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};//8字节
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};//20字节
typedef void(*VFPTR) ();

void PrintVTable(VFPTR vTable[])
{
	cout << " 虚表地址>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" 第%d个虚函数地址 :0X%x,->", i, vTable[i]);
		VFPTR f = vTable[i];
		f();
	}
	cout << endl;
}

int main()
{
	Derive d;
	VFPTR* vTableb1 = (VFPTR*)(*(int*)&d);
	PrintVTable(vTableb1);
	VFPTR* vTableb2 = (VFPTR*)(*(int*)((char*)&d + sizeof(Base1)));
	PrintVTable(vTableb2);
	return 0;
} 