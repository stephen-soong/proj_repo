#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <vector>

using namespace std;

class worker_thread
{
public:
    worker_thread(mutex& m) : mtx(m) {}
    void operator()()
    {
        lock_guard<mutex> guard(mtx);
        cout << "worker thread " << std::this_thread::get_id() << endl;
    }
private:
    mutex &mtx;
};

int main()
{
    mutex mtx;
    vector<thread> threads;
    for (int i = 0; i < 10; i++)
    {
        threads.push_back(thread((worker_thread(mtx))));
    }

    cout << "wait for all workers to finish" << endl;
    for_each(threads.begin(), threads.end(), mem_fn(&thread::join));

    cout << "main exits..." << endl;
    return 0;
}
