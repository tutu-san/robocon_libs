/**
 * @file robomas_rotation.hpp
 * @brief robomas_rotation header file
 * @details ロボマスモーターの回転指令を行うクラス、メソッドの実装は robomas_rotation.cppを参照されたい
 */
#pragma once
#ifndef ROBOMAS_ROTATION
#define ROBOMAS_ROTATION

#include "device_dependent_code/can.hpp"
// #include "canfd.hpp"

#include <cstdint>
#include <algorithm>
#include "../tools/tools.hpp"

class robomas_rotation{
protected:
    constexpr static uint32_t robomas_can_id = 0x200;
    void* can_handle;
    void convert_to_send_data(const float(&)[4], uint8_t(&)[8]);
    float robomas_pwm_data[4] = {0.0f};
public:
    robomas_rotation(void* _can_handle): can_handle(_can_handle){}
    void rotate();
    void input_rotation_data(int, float);
};
#endif