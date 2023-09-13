//////////////////////////////////////////////////////////////////////
// 文件名称：main.cpp
// 功能描述：如何实现 classA 与 B 互为友元，即 A 可以访问 B 的私有，B 也可以访问 A 的私有呢
// 创建标识：fanjialong 2023-09-13
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;
//必须提前声明class B不然编译会报错
class B;
class A{
private:
    int a;
public:
    friend class B;

    A(){
        cout << "类A被构造" << endl;
        a = 20;
    }
    ~A(){
        cout << "类A被析构" << endl;
    }
    void show(B & b);
};

class B{
private:
    int b;
public:
    friend class A;
    B(){
        cout << "类B的构造" << endl;
        b = 12;
    }
    ~B(){
        cout << "类B被析构" << endl;
    }
    void show(A &a){
        cout << "a="<<a.a ;
        cout << " b=" <<b<<endl;
    }
};
//函数不能放在class A 中，不然会编译报错
void A::show(B &b){
    cout << "a="<<a ;
    cout << " b="<<b.b<< endl;
}

int main(){
    A a;
    B b;
    a.show(b);
    b.show(a);

    return 0;
}
