#include "pi_class.hpp"
float pi_class::pi_calc(float current_value){
    //計算
    float error = 0.0f; //エラー値(目標との差)

    error = terget_value - current_value;
    integral += error; //積分を差分の累積で代用
    //Anti-windupを入れること

    //gainをかける
    float result_p = 0.0f, result_i = 0.0f;
    result_p = error * gain_p;
    result_i = integral * gain_i;

    //計算結果を返す
    float pi_result = 0.0f;
    pi_result = result_p * result_i;
    //pi制御の結果そのものにクランプをかけるのは、結果を受け取ったメソッドで行うべき
    return pi_result;
}

void pi_class::update_terget(float new_terget_value){
    terget_value = new_terget_value;
    return;
}

void pi_class::reset_integral(){
    integral = 0.0f;
    return;
}