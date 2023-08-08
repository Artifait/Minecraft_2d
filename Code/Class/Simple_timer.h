#ifndef Simple_timer_h
#define Simple_timer_h

#include <chrono>
#include <iostream>

class SimpleTimer {
public:
    SimpleTimer() {
        start_time = std::chrono::steady_clock::now();
    }

    int Get_elepside_time()
    {
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        return elapsed_milliseconds;

    }
    ~SimpleTimer() {
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_milliseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
        std::cout << "The lifetime of this object was " << elapsed_milliseconds << " microseconds." << std::endl;
    }

private:
    std::chrono::steady_clock::time_point start_time;
};
#endif