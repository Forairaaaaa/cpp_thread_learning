// dead_lock.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::chrono;


std::mutex m1;
std::mutex m2;


int main()
{
    std::thread t1([]()
        {
            m1.lock();
            std::this_thread::sleep_for(seconds(1));

            // Stuck 
            m2.lock();

            std::cout << "t1 shit\n";

            m2.unlock();
            m1.unlock();
        });



    std::thread t2([]()
        {
            m2.lock();
            std::this_thread::sleep_for(seconds(1));

            // Stuck 
            m1.lock();

            std::cout << "t2 shit\n";

            m1.unlock();
            m2.unlock();
        });



    t1.join();
    t2.join();
}
