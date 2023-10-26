// cpp_thread_leaning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>


using namespace std::chrono;

#define ull unsigned long long

static ull _odd_sum;
static ull _even_sum;

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
		_print_shit("- no shit", spent_time);
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
		_print_shit("- yes shit", spent_time);
	}

	void runShitMoreThreading()
	{
		_odd_sum = 0;
		_even_sum = 0;

		auto start_time = high_resolution_clock::now();

		// TODO lack of some locking shit 

		ull start = 0;
		ull end = 1900000000;

		// Slice
		std::vector<std::thread> thread_list;
		int chunk_size = 10000000;
		int chunk_num = (end - start) / chunk_size;
		for (ull i = 0; i < chunk_num; i++)
		{
			ull chunk_start = start + (i * chunk_size);
			ull chunk_end = start + (i * chunk_size) + chunk_size;

			if (i != 0)
				chunk_start += 1;

			//std::cout << chunk_start << "~" << chunk_end << "\n";
			thread_list.push_back(std::thread(_get_even_sum, chunk_start, chunk_end));
			thread_list.push_back(std::thread(_get_odd_sum, chunk_start, chunk_end));
		}
		// Remainder
		if (end % chunk_size != 0)
		{
			//std::cout << end - (end % chunk_size) << "~" << end << "\n";
			thread_list.push_back(std::thread(_get_even_sum, end - (end % chunk_size), end));
			thread_list.push_back(std::thread(_get_odd_sum, end - (end % chunk_size), end));
		}


		for (auto& t : thread_list)
		{
			t.join();
		}
		



		double spent_time = (double)(duration_cast<microseconds>(high_resolution_clock::now() - start_time).count()) / 1000000;
		_print_shit("- yes yes shit", spent_time);
	}

private:
	void _print_shit(std::string who, double& spentTime)
	{
		std::cout << who << ":\n" << "get: " << _even_sum << " " << _odd_sum << "\n";
		std::cout << "spent time: " << spentTime << "s\n";
	}
};




int main()
{
	ThreadSimpleCompare test;

	test.runShit();
	test.runShitThreading();
	test.runShitMoreThreading();
}
