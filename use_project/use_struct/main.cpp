#include <iostream>

using namespace std;

enum ETest
{
    eA,
    eB,
};

struct EStruct
{
    int a;
    int b;
};

typedef struct tagEStruct
{
    int a;
    int b;
}EStruct2;

int main()
{
    EStruct2 a;
    EStruct b;
    ETest c = eA;
    ETest d = ETest::eB;
    return 0;
}
