// condition_variable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std::chrono;


int shit_num = 0;
std::mutex shit_mutex;
std::condition_variable shit_cv;


int main()
{
    std::thread t1([]()
        {
            std::this_thread::sleep_for(seconds(2));

            std::cout << "t1 wait mutex\n";
            std::unique_lock<std::mutex> lock(shit_mutex);
            std::cout << "t1 get mutex\n";

            shit_num = 6;
            std::cout << "t1 set shit 6\n";
            shit_cv.notify_one();

            shit_num = 114514;
            std::cout << "t1 set shit 114514\n";
            shit_cv.notify_one();

            std::cout << "t1 bye\n";
        });


    std::thread t2([]()
        {
            std::unique_lock<std::mutex> lock(shit_mutex);

            std::cout << "t2 wait shit\n";

            // Check condition -> Unlock -> Wait notify
            // Get notify -> Check condition ...
            shit_cv.wait(lock, []() { return shit_num > 100 ? true : false; });
            std::cout << "t2 haha get shit: " << shit_num << "\n";
        });



    t1.join();
    t2.join();
}
