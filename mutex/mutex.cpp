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


int main()
{
    // Mutual Exclusion
    mutex_shit();
}


