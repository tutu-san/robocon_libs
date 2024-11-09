/**
 * @file pi_class.hpp
 * @brief pi_class header file
 * @details PI制御を行うクラスが入っている、メソッドの実装は pi_class.cppを参照されたい
 */
#pragma once
#ifndef PI_CLASS
#define PI_CLASS

//include
#include <cstdint>
#include <cfloat>
#include "../tools/tools.hpp"

//class
class pi_class{
private:
    //gain
    float gain_p;
    float gain_i;
    float gain_d;
    //delta_t(loop_time/コンストラクタで設定できるようにする) (単位 sec)
    const float delta_t;

    //目標値の上限・下限(初期値は無限)
    float target_upper_limit = FLT_MAX;
    float target_lower_limit = -FLT_MAX;
    //積分累積値
    float integral = 0.0f;
    //前回の差分値(d制御準備工事)
     float prev_error = 0.0f;
    //PI制御のON/OFF
    bool pi_on = true;
    //PI制御計算の本体
    float pi_calc(float);
    float _debug_result = 0.0f;
public:
    //コンストラクタ
    pi_class(float _gain_p, float _gain_i, float _gain_d, float _delta_t):gain_p(_gain_p), gain_i(_gain_i), gain_d(_gain_d), delta_t(_delta_t){}
    float run_pi_controller(float);
    void update_target(float);
    void set_target_limit(float, bool);
    void reset_integral();
    void pi_enabled(bool);
    void update_p_gain(float);
    void update_i_gain(float);
    float show_error();

    //目標値
        float target_value = 0.0f;
};

#endif
