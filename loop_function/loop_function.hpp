#pragma once
#ifndef LOOP_FUNC
#define LOOP_FUNC

#include <functional>

class loop_function{
private:
    int execution_interval; //ms
    std::function<void()>function;
    int elapsed_time_after_execution = 0; //ms
public:
    loop_function(std::function<void()> _function, int _interval):
function(_function), execution_interval(_interval) {}
    void execute(int);
    void change_interval(int);
};

#endif