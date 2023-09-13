#include <iostream>

using namespace std;

class CFunctorBase
{
public:
    virtual ~CFunctorBase()
    {

    }
    virtual int operator()(int a, int b) noexcept = 0;
};

class CFunctor : public CFunctorBase
{
public:
    int operator()(int a, int b) noexcept override
    {
        return a + b;
    }
} CFunctorInstance;

int Test(CFunctorBase& base)
{
    return base(2, 3);
}

int main()
{
    cout << CFunctorInstance(1, 2) << endl;
    cout << Test(CFunctorInstance) << endl;
    return 0;
}
