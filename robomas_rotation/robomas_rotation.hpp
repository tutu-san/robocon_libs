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
    void* can_handle;
    void convert_to_send_data(const float(&)[4], uint8_t(&)[8]);
    float robomas_pwm_data[4] = {0.0f};
	int16_t robomas_int16_pwm_data[4]; //float to int
public:
    robomas_rotation(void* _can_handle): can_handle(_can_handle){}
    float motor_max_power[4]{};
    void rotate();
    void input_rotation_data(int, float);
    float show_pwm_data(int);
    void select_max_power(uint8_t, uint8_t);
};
#endif
