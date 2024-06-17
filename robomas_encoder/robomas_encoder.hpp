/**
 * @file robomas_rotation.hpp
 * @brief robomas_rotation header file
 * @details ロボマスモーターのエンコーダー処理を行うクラス、メソッドの実装は robomas_encoder.cppを参照されたい
 */

#pragma once
#ifndef ROBOMAS_ENCODER
#define ROBOMAS_ENCODER

#include <cstdint>

enum class robomas_motor_type_enum : int {
    M2006,
    M3508,
};

class robomas_encoder{
private:
    uint8_t robomas_input_rpm_high = 0, robomas_input_rpm_low = 0; //save robomas_encoder_data
    uint8_t robomas_input_pos_high = 0, robomas_input_pos_low = 0;
    int16_t debug_robomas_rpm = 0;
    int16_t signed_robomas_pos_data = 0;
    float signed_robomas_pos_axis_data = 0.0f;
    float debug_robomas_pos = 0.0f;
    float save_before_axis_pos = 0.0f;
    int default_position = 0;

    float ruisekiwa = 0.0f;

    float motor_gear_ratio;
public:
    robomas_encoder(robomas_motor_type_enum _motor_type){
        switch(_motor_type){
            case robomas_motor_type_enum::M2006:
                motor_gear_ratio = 36.0f;
                break;
            case robomas_motor_type_enum::M3508:
                motor_gear_ratio = 3591.0f / 187.0f;
                break;
        }
    }

    void input_encoder_data(uint8_t[8]);
    int show_rpm();
    float show_pos();
    void reset_positon(int new_default_position = 0);

    void first_axis_pos();
};

#endif