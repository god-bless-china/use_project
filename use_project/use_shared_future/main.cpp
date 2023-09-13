#include <iostream>
#include <future>
#include <thread>

int main()
{
    std::promise<int> prom;
    auto fu = prom.get_future();
    auto shared_fu = fu.share();
    auto f1 = std::async(std::launch::async, [shared_fu]()
    {
        std::cout << shared_fu.get();
    });
    auto f2 = std::async(std::launch::async, [shared_fu]()
    {
        std::cout << shared_fu.get();
    });
    prom.set_value(102);
    f1.get();
    f2.get();
    return 0;
}
