#include "loop_function.hpp"

void loop_function::change_interval(int new_interval){
    execution_interval = new_interval;
}

void loop_function::execute(int timer_interval_time){
    elapsed_time_after_execution += timer_interval_time;
    if(elapsed_time_after_execution >= execution_interval){
        function();
        elapsed_time_after_execution = 0;
    }
    return;
}