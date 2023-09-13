// https://zhuanlan.zhihu.com/p/348312534

/* C ++程序演示友元函数的工作。*/

/*
 * 要访问数据，应该在类的内部以关键字 friend 开始声明友元函数
 * (可以是类内部的任何地方，
 * 可以是private部分，
 * 也可以是public部分)
 */

#include <iostream>
using namespace std;

class Distance
{
    private:
        int meter;
    public:
        Distance(): meter(0) { }
        //友元函数
        friend int addFive(Distance);
};

// 友元函数的定义
int addFive(Distance d)
{
    //从非成员函数访问私有数据
    d.meter += 5;
    return d.meter;
}

int main()
{
    Distance D;
    cout << "distance: " << addFive(D) << endl;
    return 0;
}
