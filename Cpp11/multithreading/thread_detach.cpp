#include <iostream>
#include <thread>

using namespace std;

int main()
{
    thread worker([] {
        for (int i = 0; i < 100; i++)
        {
            cout << "workder thread is running " + to_string(i) << endl;
        }
    });

    for (int i = 0; i < 50; i++)
    {
        cout << "main thread is running " + to_string(i) << endl;
    }

    if (worker.joinable())
    {
        cout << "detach worker" << endl;
        worker.detach();
    }
    
    if (worker.joinable()) {
        cout << "detack worker again" << endl;
        worker.detach();
    }

    return 0;
}