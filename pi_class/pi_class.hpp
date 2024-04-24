/**
 * @file pi_class.hpp
 * @brief pi_class header file
 * @details PI制御を行うクラスが入っているクラス、メソッドの実装は pi_class.cppを参照されたい
 */
#pragma once
#ifndef PI_CLASS
#define PI_CLASS

//include
#include <cstdint>
#include "../tools/tools.hpp"

//class
class pi_class{
private:
    //gain
    float gain_p;
    float gain_i;
    //delta_t(loop_time/コンストラクタで設定できるようにする)
    const float delta_t;
    //目標値
    float terget_value = 0.0f;
    //積分累積値
    float integral = 0.0f;
    //PI制御のON/OFF
    bool pi_on = true;
    //PI制御計算の本体
    float pi_calc(float);
public:
    //コンストラクタ
    pi_class(float _gain_p, float _gain_i, float _delta_t):gain_p(_gain_p), gain_i(_gain_i), delta_t(_delta_t){}
    float run_pi_controller(float);
    void update_terget(float);
    void reset_integral();
    void pi_enabled(bool);
    void update_p_gain(float);
    void update_i_gain(float);
};

#endif