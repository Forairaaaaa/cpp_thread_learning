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
            std::this_thread::sleep_for(seconds(2));

            if (tm.try_lock_for(seconds(1)))
            {
                std::cout << "t2 shitting\n";
                tm.unlock();
            }
            else
            {
                std::cout << "t2 shit on pants\n";
            }

            std::cout << "t2 done\n";
        });

    t1.join();
    t2.join();
}



//std::mutex rm;
std::recursive_mutex rm;
int rm_shit = 0;

void recursive_shit(std::string name)
{
    rm.lock();
    rm_shit--;
    
    if (rm_shit > 0)
    {
        std::cout << name << " i: " << rm_shit << "\n";
        recursive_shit(name);
    }
    rm.unlock();
}

void recursive_mutex_shit()
{
    std::thread t1([]()
        {
            rm.lock();
            rm_shit = 666;
            //rm_shit = 114514;
            recursive_shit("t1");
            rm.unlock();
        });

    std::thread t2([]()
        {
            rm.lock();
            rm_shit = 666;
            //rm_shit = 114514;
            recursive_shit("t2");
            rm.unlock();
        });

    t1.join();
    t2.join();
}



std::mutex lgm;

// Auto unlock when out of scope 
void lock_guard_shit()
{
    std::thread t1([]()
        {
            std::lock_guard<std::mutex> lock(lgm);
            std::cout << "t1 haha\n";
            std::this_thread::sleep_for(seconds(4));
        });

    std::this_thread::sleep_for(seconds(1));

    std::thread t2([]()
        {
            std::cout << "t2 waiting\n";
            std::lock_guard<std::mutex> lock(lgm);
            std::cout << "t2 haha\n";
        });

    t1.join();
    t2.join();
}



int main()
{
    // Mutual Exclusion
    //mutex_shit();
    //timed_mutex_shit();
    //recursive_mutex_shit();
    lock_guard_shit();
}


