#include<iostream>
using namespace std;

//��̬����������
//1���麯������д
//2����������ָ���������ȥ�����麯��

// �����̬����ָ�����������޹أ�ָ���ĸ�������þ��������麯��
//�������̬�������ö���������йأ�������ʲô���õľ���˭���麯��
 
//class Person 
//{
//public:
//	virtual void BuyTicket() { cout << "��Ʊ-ȫ��" << endl; }
//};
//class Student : public Person
//{
//public:
//	virtual void BuyTicket() { cout << "��Ʊ-���" << endl; }
//	/*ע�⣺����д�����麯��ʱ����������麯���ڲ���virtual�ؼ���ʱ����ȻҲ���Թ�����д(��Ϊ��
//	�к������麯�����̳������������������ɱ����麯������),���Ǹ���д�����Ǻܹ淶������������ʹ��
//	*/
//	/*void BuyTicket() { cout << "��Ʊ-���" << endl; }*/
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
//	//���������ĺ������ᱻ�����destructor
//};
//
//class Student : public Person {
//public:
//	virtual ~Student() { cout << "Student::~Student()" << endl; }
	//���������ĺ������ᱻ�����destructor
	//override ���������麯���Ƿ���д�˸�����麯��
//};
// ֻ��������Student������������д��Person�����������������delete���������������������
//���ɶ�̬�����ܱ�֤p1��p2ָ��Ķ�����ȷ�ĵ�������������
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

//������
//class Car
//{
//public:
//	virtual void Drive() = 0;//���麯�� ����Ҫʵ��
//};
////���麯��������
////1��ǿ������ȥ�����д
////2����ʾ��������͡������������ʵ��û�ж�Ӧ��ʵ���
//class Benz :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "Benz-����" << endl;
//	}
//};
//class BMW :public Car
//{
//public:
//	virtual void Drive()
//	{
//		cout << "BMW-�ٿ�" << endl;
//	}
//};
//void Test()
//{
//	Car* pBenz = new Benz;//����ָ��ָ���������
//	pBenz->Drive();
//	Car* pBMW = new BMW;
//	pBMW->Drive();
//}
//
//int main()
//{
//	//Car car;//�����಻��ʵ����������
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
//{	//ȡ�������ǰ4���ֽ�
//	Base b1;
//	printf("vfptr:%p\n", *(int*)&b1);
//	 
//	int i = 0;
//	int* p1 = &i;
//	int* p2 = new int;
//	char* p3 = "hello";
//	printf("ջ����:%p\n", p1);
//	printf("�ѱ���:%p\n", p2);
//	printf("����α���:%p\n", p3);
//	printf("����κ�����ַ:%p\n", &Base::Func3);
//	printf("������麯����ַ:%p\n", &Base::Func1);
//}
//
//int main()
//{
//	//Base b;
//	//Derive d;
//	//test1();
//	int i = 0;
//	double d = 1.1;
//	//��̬�󶨾�̬�Ķ�̬(��̬:����ʱȷ��������ַ)
//
//	//��̬�󶨶�̬�Ķ�̬(��̬:����ʱ����������麯����ַ>
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
////void(*p)();//����һ������ָ�����
//typedef void(*VF_PTR)();//����ָ������typedef
//void printVFTable(VF_PTR* pTable)//��ӡ���̳�����������ڴ�������޷��鿴��func3��cunc4
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
};//8�ֽ�
class Base2 {
public:
	virtual void func1() { cout << "Base2::func1" << endl; }
	virtual void func2() { cout << "Base2::func2" << endl; }
private:
	int b2;
};//8�ֽ�
class Derive : public Base1, public Base2 {
public:
	virtual void func1() { cout << "Derive::func1" << endl; }
	virtual void func3() { cout << "Derive::func3" << endl; }
private:
	int d1;
};//20�ֽ�
typedef void(*VFPTR) ();

void PrintVTable(VFPTR vTable[])
{
	cout << " ����ַ>" << vTable << endl;
	for (int i = 0; vTable[i] != nullptr; ++i)
	{
		printf(" ��%d���麯����ַ :0X%x,->", i, vTable[i]);
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