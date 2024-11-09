#pragma once
#ifndef LOOP_FUNC
#define LOOP_FUNC

#include <functional>
#include "../tools/tools.hpp"

class interrupt_function_base{
protected:
    int execution_interval; //ms (関数の実行間隔設定)
    int elapsed_time_after_execution = 0; //ms (前回の実行からの経過時間)
public:
    interrupt_function_base(int _execution_interval){
        execution_interval = _execution_interval > 0 ? _execution_interval : 0;
    }
    void change_interval(int);
};

class interrupt_function_no_argment : public interrupt_function_base{
private:
    void (*function)();
public:
    interrupt_function_no_argment(void(*_function)(), int _execution_interval)
    :function(_function), interrupt_handler_base(_execution_interval){}
    void execute(int);
};

class timer_function : interrupt_function_base{
private:
    void (*function)(bool);
public:
    timer_function(void(*_function)(bool), int _execution_interval)
    :function(_function), interrupt_handler_base(_execution_interval){}
    void execute(int);
};

#endif