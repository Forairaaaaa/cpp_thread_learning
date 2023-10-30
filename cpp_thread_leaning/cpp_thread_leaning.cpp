// cpp_thread_leaning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <string>


using namespace std::chrono;

#define ull unsigned long long

static ull _odd_sum;
static ull _even_sum;
std::mutex _odd_sum_lock;
std::mutex _even_sum_lock;

void _get_even_sum(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 == 0)
            _even_sum += i;
    }
}

void _get_odd_sum(ull start, ull end)
{
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 != 0)
            _odd_sum += i;
    }
}

void _get_even_sum_with_lock(ull start, ull end)
{
    ull buffer = 0;
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 == 0)
            buffer += i;
    }
    _even_sum_lock.lock();
    _even_sum += buffer;
    _even_sum_lock.unlock();
}

void _get_odd_sum_with_lock(ull start, ull end)
{
    ull buffer = 0;
    for (ull i = start; i <= end; i++)
    {
        if (i % 2 != 0)
            buffer += i;
    }
    _odd_sum_lock.lock();
    _odd_sum += buffer;
    _odd_sum_lock.unlock();
}


class ThreadSimpleCompare
{
public:
    void runShit()
    {
        _odd_sum = 0;
        _even_sum = 0;

        auto start_time = high_resolution_clock::now();

        _get_even_sum(0, 1900000000);
        _get_odd_sum(0, 1900000000);

        double spent_time = (double)(duration_cast<microseconds>(high_resolution_clock::now() - start_time).count()) / 1000000;
        _print_shit("- 1 thread", spent_time);
    }

    void runShitThreading()
    {
        _odd_sum = 0;
        _even_sum = 0;

        auto start_time = high_resolution_clock::now();

        std::thread t1(_get_even_sum, 0, 1900000000);
        std::thread t2(_get_odd_sum, 0, 1900000000);

        t1.join();
        t2.join();

        double spent_time = (double)(duration_cast<microseconds>(high_resolution_clock::now() - start_time).count()) / 1000000;
        _print_shit("- 2 threads", spent_time);
    }

    void runShitMoreThreading(ull chunk_size = 10000000)
    {
        _odd_sum = 0;
        _even_sum = 0;

        auto start_time = high_resolution_clock::now();

        ull start = 0;
        ull end = 1900000000;

        // Slice
        std::vector<std::thread> thread_list;

        //// 380 threads finish in: 1.1966s
        //ull chunk_size = 10000000;

        //// 3800 threads finish in: 4.53975s
        //ull chunk_size = 1000000;

        //// 38 threads finish in: 1.00333s
        //ull chunk_size = 100000000;



        ull chunk_num = (end - start) / chunk_size;
        for (ull i = 0; i < chunk_num; i++)
        {
            ull chunk_start = start + (i * chunk_size);
            ull chunk_end = start + (i * chunk_size) + chunk_size;

            if (i != 0)
                chunk_start += 1;

            //std::cout << chunk_start << "~" << chunk_end << "\n";
            thread_list.push_back(std::thread(_get_even_sum_with_lock, chunk_start, chunk_end));
            thread_list.push_back(std::thread(_get_odd_sum_with_lock, chunk_start, chunk_end));
        }
        // Remainder
        if (end % chunk_size != 0)
        {
            //std::cout << end - (end % chunk_size) << "~" << end << "\n";
            thread_list.push_back(std::thread(_get_even_sum_with_lock, end - (end % chunk_size), end));
            thread_list.push_back(std::thread(_get_odd_sum_with_lock, end - (end % chunk_size), end));
        }

        // Wait finish 
        for (auto& t : thread_list)
        {
            t.join();
        }


        double spent_time = (double)(duration_cast<microseconds>(high_resolution_clock::now() - start_time).count()) / 1000000;
        std::string shit;
        shit = "- ";
        shit += std::to_string(thread_list.size());
        shit += " threads";
        _print_shit(shit, spent_time);
    }

private:
    void _print_shit(std::string how, double& spentTime)
    {
        std::cout << how << " \tfinish in: " << spentTime << "s\t";
        std::cout << "(get: " << _even_sum << " " << _odd_sum << ")\n";
    }
};




int main()
{
    ThreadSimpleCompare test;

    test.runShit();
    test.runShitThreading();
    test.runShitMoreThreading(100000000);
    test.runShitMoreThreading(10000000);
    test.runShitMoreThreading(1000000);
}
