// mutex.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

using namespace std::chrono;


int shit_num = 0;
std::mutex shit_mutex;


static void poop_one_shit()
{
    //auto shit = shit_num;
    //std::this_thread::sleep_for(milliseconds(2));
    //shit_num = shit + 1;


    shit_mutex.lock();
    auto shit = shit_num;
    std::this_thread::sleep_for(milliseconds(2));
    shit_num = shit + 1;
    shit_mutex.unlock();
}


void mutex_shit()
{
    std::vector<std::thread> thread_list;

    for (int i = 0; i < 100; i++)
        thread_list.push_back(std::thread(poop_one_shit));

    for (auto& i : thread_list)
        i.join();

    std::cout << "ShitNum:      " << shit_num << std::endl;
}


std::timed_mutex tm;

void timed_mutex_shit()
{
    std::thread t1([]()
        {
            if (tm.try_lock_for(seconds(10)))
            {
                std::cout << "t1 shitting\n";

                std::this_thread::sleep_for(seconds(4));
                tm.unlock();
            }

            std::cout << "t1 done\n";
        });

    std::thread t2([]()
        {
            std::this_thread::sleep_for(seconds(1));

            if (tm.try_lock_for(seconds(1)))
            {
                std::cout << "t2 shitting\n";
                tm.unlock();
            }
            else
            {
                std::cout << "t2 shit on pants\n";
            }
        });

    t1.join();
    t2.join();
}


int main()
{
    // Mutual Exclusion
    //mutex_shit();
    timed_mutex_shit();
}


