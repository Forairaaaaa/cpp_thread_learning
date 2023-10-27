// join_and_detach.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;


void eat_shit(int shit)
{
    std::this_thread::sleep_for(seconds(3));

    while (shit-- > 0)
        std::cout << shit << std::endl;
}


void join_shit()
{
    std::thread t1(eat_shit, 2);

    std::cout << "shit\n";
    t1.join();
    std::cout << "shit???\n";

    //t1.join();
    if (t1.joinable())
        t1.join();
}


void detach_shit()
{
    std::thread t1(eat_shit, 2);

    //t1.join();
    t1.detach();
}


int main()
{
    //join_shit();
    detach_shit();
}
