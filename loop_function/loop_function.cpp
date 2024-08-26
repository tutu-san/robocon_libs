#include "loop_function.hpp"

void interrupt_handler_base::change_interval(int new_interval){
    execution_interval = (new_interval > 0 ? new_interval : 0);
}


void interrupt_handler_no_argment::execute(int timer_interval_time){
    if(execution_interval == 0) return; //intervalが0に設定されている場合実行されなくなる
    elapsed_time_after_execution += (timer_interval_time > 0 ? timer_interval_time : 0); //<-タイマー1実行あたりの経過時間
    if(elapsed_time_after_execution >= execution_interval){
        function();
        elapsed_time_after_execution = 0;
    }
    return;
}

void timer_function::execute(int timer_interval_time){
    if(execution_interval == 0) return;
    elapsed_time_after_execution += (timer_interval_time > 0 ? timer_interval_time : 0);
    if(elapsed_time_after_execution >= execution_interval){
        function(true);
        elapsed_time_after_execution = 0;
        return;
    }else{
        function(false);
        return;
    }
}