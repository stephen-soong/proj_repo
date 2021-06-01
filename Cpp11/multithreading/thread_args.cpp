#include <iostream>
#include <thread>
#include <string>

using namespace std;

void thread_func_1(int x, string str) {
    cout << "worker receive " << x << endl;
    cout << "worker receive " << str << endl;
}

void thread_func_2(int const & x) {
    int &y = const_cast<int &>(x);
    y++;
    cout << "worker changes x to " << x << endl;
}

void thread_func_3(int & x) {
    x++;
    cout << "worker changes x to " << x << endl;
}

class worker {
public:
    worker() {}
    worker(const worker& obj) {}
    void foo(int x) {
        cout << "worker receive " << x << endl;
    }
};

int main() {
    thread worker_1(thread_func_1, 100, "test");
    worker_1.join();

    int x = 10;
    cout << "main has x is " << x << endl;

    thread worker_2(thread_func_2, x);
    worker_2.join();
    cout << "main has x is " << x << endl;

    thread worker_3(thread_func_3, std::ref(x));
    worker_3.join();
    cout << "main has x is " << x << endl;

    worker w;
    thread worker_4(&worker::foo, &w, 50);
    worker_4.join();
    return 0;
}