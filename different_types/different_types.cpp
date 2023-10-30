// different_types.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>



/// Function pointer and lambda 
void lamda_shit()
{
    auto shit = [](int shit)
        {
            while (shit-- > 0)
                std::cout << shit << std::endl;
        };

    std::thread t1(shit, 11);
    t1.join();


    std::thread t2([](int shit)
        {
            while (shit-- > 0)
                std::cout << shit << std::endl;
        }, 6);
    t2.join();
}



/// Functor (Function object)
/// https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses
class DogShit
{
public:
    void operator ()(int shit)
    {
        while (shit-- > 0)
            std::cout << shit << std::endl;
    }
};

void functor_shit()
{
    std::thread t1(DogShit(), 10);
    t1.join();
}



/// Non static method  
class BullShit
{
public:
    void shit(int shit)
    {
        //while (true)
        //    std::cout << "?\n";

        while (shit-- > 0)
            std::cout << shit << std::endl;
    }
};

void non_static_method_shit()
{
    BullShit shit;
    std::thread t1(&BullShit::shit, &shit, 10);
    t1.join();

    //// Useless :(
    //auto shit = new BullShit;
    //std::thread t1(&BullShit::shit, shit, 10);
    //delete shit;
    //t1.join();
}



/// Static method
class FuckThatShit
{
public:
    static void shit(int shit)
    {
        while (shit-- > 0)
            std::cout << shit << std::endl;
    }
};

void static_method_shit()
{
    std::thread t1(&FuckThatShit::shit, 10);
    t1.join();
}



int main()
{
    //lamda_shit();
    //functor_shit();
    //non_static_method_shit();
    static_method_shit();
}

