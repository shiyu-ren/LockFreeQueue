
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

#include "LockFreeQueue.hpp"

LockFreeQueue<int, 20> lf_que;

int n = 30;
std::mutex m;

void producer()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    for(int i = 0; i < n; ++i)
    {
        while(!lf_que.push(i));
        // lock.lock();
        // std::cout << "producer push: " << i << "\n";
        // lock.unlock();
    }
}

void consumer()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    for(int i = 0; i < n; ++i)
    {
        int result;
        while(!lf_que.pop(result));
        // lock.lock();
        std::cout << "consumer get: " << result << "\n";
        // lock.unlock();
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();
}
