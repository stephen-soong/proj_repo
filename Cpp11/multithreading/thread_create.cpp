#include <iostream>
#include <thread>
#include <string>

using namespace std;
constexpr int LOOP_COUNT = 100;

void func_ptr()
{
    for (int i = 0; i < LOOP_COUNT; i++)
        cout << "func_ptr executing " + to_string(i) << endl;
}

class func_obj
{
public:
    void operator()()
    {
        for (int i = 0; i < LOOP_COUNT; i++)
            cout << "func_obj executing " + to_string(i) << endl;
    }
};

int main()
{
    thread thread1(func_ptr);

    func_obj f;
    thread thread2(f);

    auto l = [] {
        for (int i = 0; i < LOOP_COUNT; i++)
            cout << "lambda executing " + to_string(i) << endl;
    };
    thread thread3(l);

    for (int i = 0; i < LOOP_COUNT; i++)
        cout
            << "main executing " + to_string(i) << endl;

    cout << "join " << thread1.get_id() << endl;
    thread1.join();

    cout << "join " << thread2.get_id() << endl;
    thread2.join();

    cout << "join " << thread3.get_id() << endl;
    thread3.join();

    cout << "main exit" << endl;
    return 0;
}