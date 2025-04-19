/**
 * @file robomas_rotation.hpp
 * @brief robomas_rotation header file
 * @details ロボマスモーターの回転指令を行うクラス、メソッドの実装は robomas_rotation.cppを参照されたい
 */
#pragma once
#ifndef ROBOMAS_ROTATION
#define ROBOMAS_ROTATION

#include "device_dependent_code/can.hpp"
#include "device_dependent_code/canfd.hpp"

#include <cstdint>
#include <algorithm>
#include "../tools/tools.hpp"

class robomas_rotation{
protected:
    constexpr static uint32_t robomas_can_id = 0x200;
    can_transmit* can_transmitter;
    void convert_to_send_data(const float(&)[4], uint8_t(&)[8]);
    float robomas_ratio_data[4] = {};
    float robomas_pwm_data[4] = {0.0f};
	int16_t robomas_int16_pwm_data[4]; //float to int
	float motor_max_power[4]{10000, 10000, 10000, 10000};
public:
    robomas_rotation(can_transmit* _can_transmitter): can_transmitter(_can_transmitter){}
    void rotate();
    void input_rotation_data(int, float);
    float show_ratio(int);
    float show_pwm_data(int);
    float show_max_motor_power(int);
    void select_max_power(uint8_t, uint8_t);
};
#endif
