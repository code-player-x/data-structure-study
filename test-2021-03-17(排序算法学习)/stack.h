#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
// 下面是定长的静态栈的结构，实际中一般不实用，所以我们主要实现下面的支持动态增长的栈
typedef int STDataType;
//#define N 10
//typedef struct Stack
//{
//      STDataType _a[N];
//      int _top; // 栈顶
//}Stack;
// 支持动态增长的栈
typedef int STDataType;
typedef struct Stack
{
    STDataType* _a;
    int _top; // 栈顶
    int _capacity; // 容量
}Stack;
// 初始化栈
void StackInit(Stack* ps)
{
    ps->_a = 0;
    ps->_top = 0;
    ps->_capacity = 0;
}
// 入栈
void StackPush(Stack* ps, STDataType data)
{
    assert(ps);
    if (ps->_top == ps->_capacity)//判断栈是否是满的
    {
        size_t newcapacity = ps->_capacity == 0 ? 4 : ps->_capacity * 2;
        ps->_a = (STDataType*)realloc(ps->_a, newcapacity * sizeof(STDataType));
        ps->_capacity = newcapacity;
    }
    ps->_a[ps->_top] = data;
    ps->_top++;
}
// 出栈
void StackPop(Stack* ps)
{
    assert(ps && ps->_top > 0);
    --ps->_top;
}
// 获取栈顶元素
STDataType StackTop(Stack* ps)
{
    assert(ps);
    return ps->_a[ps->_top - 1];
}
// 获取栈中有效元素个数
int StackSize(Stack* ps)
{
    assert(ps);
    return ps->_top;
}
// 检测栈是否为空，如果为空返回非零结果(1)，如果不为空返回0
int StackEmpty(Stack* ps)
{
    assert(ps);
    return  ps->_top == 0 ? 1 : 0;
}
// 销毁栈
void StackDestroy(Stack* ps)
{
    assert(ps);
    free(ps->_a);
    ps->_a = NULL;
    ps->_top = ps->_capacity = 0;
}
