
#include <iostream>
#include <thread>
#include <mutex>
#include <memory>

#include "LockFreeQueueN2N.hpp"

LockFreeQueue<int> lf_que;

int n = 10;
// std::mutex m;

void producer1()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    std::cout << "producer " << std::this_thread::get_id() << " start work\n";
    for(int i = n*0; i < n; ++i)
    {
        while(!lf_que.push(i));
        // lock.lock();
        // std::cout << "producer push: " << i << "\n";
        // lock.unlock();
    }
}

void producer2()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    std::cout << "producer " << std::this_thread::get_id() << " start work\n";
    for(int i = n*1; i < 2*n; ++i)
    {
        while(!lf_que.push(i));
        // lock.lock();
        // std::cout << "producer push: " << i << "\n";
        // lock.unlock();
    }
}

void consumer1()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    for(int i = 0; i < n; ++i)
    {
        int result;
        while(!lf_que.pop(result));
        // lock.lock();
        std::cout << "consumer" << std::this_thread::get_id() << " get: " << result << "\n";
        // lock.unlock();
    }
}

void consumer2()
{
    // std::unique_lock<std::mutex> lock(m, std::defer_lock);
    for(int i = 0; i < n; ++i)
    {
        int result;
        while(!lf_que.pop(result));
        // lock.lock();
        std::cout << "consumer" << std::this_thread::get_id() << " get: " << result << "\n";
        // lock.unlock();
    }
}

int main()
{
    std::thread t1(producer1);
    std::thread t2(producer2);

    std::thread t3(consumer1);
    std::thread t4(consumer2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
