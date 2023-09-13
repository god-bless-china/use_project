#include <iostream>
using namespace std;

// 使用友元函数添加两个不同类的成员
// 你完全可以在不使用friend函数的情况下操作两个不同类的对象，
// 但是这个程序会很长，很复杂，很难理解。

// 前置声明
class B;
class A {
    private:
      int numA;
    public:
      A(): numA(12) { }
      //友元函数声明
      friend int add(A, B);
};

class B {
    private:
       int numB;
    public:
       B(): numB(1) { }
       // 友元函数声明
       friend int add(A , B);
};

//函数add()是类A和B的友元函数
//访问成员变量numA和numB
int add(A objectA, B objectB)
{
   return (objectA.numA + objectB.numB);
}

int main()
{
    A objectA;
    B objectB;
    cout<<"Sum: "<< add(objectA, objectB);
    return 0;
}
