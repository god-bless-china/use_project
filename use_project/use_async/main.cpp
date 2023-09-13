#include <iostream>
#include <future>
#include <thread>

int main()
{
    auto f = std::async(
                std::launch::async, [](int a, int b) { return a + b;}, 1, 2);
    std::cout << f.get() << std::endl;
    return 0;
}
