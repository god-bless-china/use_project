#include <iostream>
#include <thread>
#include <future>

using namespace std;

//int main()
//{
//    promise<bool> prom;
//    future<bool> f = prom.get_future();
//    prom.set_value(true);
//    cout << f.get() << endl;
//    return 0;
//}

int main()
{
    promise<int> prom;
    auto f = prom.get_future();
    thread t(
    [](promise<int> p)
    {
        this_thread::sleep_for(chrono::seconds(2));
        p.set_value(100);
    },
    move(prom));
    cout << f.get() << endl;
    if (t.joinable())
        t.join();
}
