#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

class Wallet
{
    int money;
    mutex mtx;

public:
    Wallet() : money(0) { }
    int getMoney() { return money; }
    void addMoney(int m)
    {
        lock_guard<mutex> guard(mtx);
        for (int i = 0; i < m; ++i)
        {
            money++;
        }
    }
};

int testMultithreadedWallet()
{
    Wallet wallet;
    vector<thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.push_back(thread(&Wallet::addMoney, &wallet, 1000));
    }

    for (int i = 0; i < threads.size(); ++i)
    {
        threads[i].join();
    }

    return wallet.getMoney();
}

int main()
{
    int val = 0;

    for (int k = 0; k < 1000; ++k)
    {
        if ((val = testMultithreadedWallet()) != 5000)
        {
            cout << "Error at count = " << k << " Money in Wallet = " << val << endl;
        }
    }

    return 0;
}