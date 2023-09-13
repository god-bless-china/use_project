//////////////////////////////////////////////////////////////////////
// 文件名称：main.cpp
// 功能描述：如何实现 classA 与 B 互为友元，即 A 可以访问 B 的私有，B 也可以访问 A 的私有呢
// 创建标识：fanjialong 2023-09-13
// 文件版权：江西博微新技术有限公司
//////////////////////////////////////////////////////////////////////
#include <iostream>

using namespace std;
class A {
private:
    int a;
public:
    friend class B;

    A(){
        cout << "A Construct ... " << endl;
        a = 20;
    }
    ~A(){
        cout << "A DeConstruct ... " << endl;
    }
};

class B{
private:
    int b = 10;
public:
    B() {
        cout << "B Construct ... " << endl;
    }
    ~B() {
        cout << "B DeConstruct ... " << endl;
    }
    int add()
    {
        A a;
        return b + a.a;
    }
};

int main(){
    B b;
    cout << b.add() << endl;
    return 0;
}
