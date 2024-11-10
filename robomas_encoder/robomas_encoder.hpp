/**
 * @file robomas_rotation.hpp
 * @brief robomas_rotation header file
 * @details ロボマスモーターのエンコーダー処理を行うクラス、メソッドの実装は robomas_encoder.cppを参照されたい
 */

#pragma once
#ifndef ROBOMAS_ENCODER
#define ROBOMAS_ENCODER

#include <cstdint>
#include <cmath>

enum class robomas_motor_type_enum : int {
    M2006,
    M3508,
};

class robomas_encoder{
private:
    float debug_robomas_rpm = 0;
    int16_t signed_robomas_pos_data = 0;
    float signed_robomas_pos_axis_data = 0.0f;
    float save_before_axis_pos = 0.0f;
    int default_position = 0;
    uint8_t robomas_input_rpm_high = 0, robomas_input_rpm_low = 0; //save robomas_encoder_data
	uint8_t robomas_input_pos_high = 0, robomas_input_pos_low = 0;
	uint8_t robomas_input_current_high = 0, robomas_input_current_low = 0;
	int16_t angle_data;
	int16_t speed_data;
	uint16_t current_data;

    float ruisekiwa = 0.0f;
    float last_data = 0.0f;

//from taichi encoder
    float update_angle(int16_t, int16_t);
    float taichi_input_target(float, float);
    constexpr static size_t resolution_bit = 13;
    constexpr static int resolution = 1<<resolution_bit;
    constexpr static float angle_to_rad = 2*M_PI/(float)resolution;
    int32_t turn_count = 0;
    int16_t old_angle = 0;
public:
    robomas_encoder(robomas_motor_type_enum _motor_type){
        change_motor_type(_motor_type);
    }

    float motor_gear_ratio;
    float result_pos = 0.0f;

    void change_motor_type(robomas_motor_type_enum motor_type);
    void input_encoder_data(uint8_t[8]);
    float show_rpm();
    float show_pos();
    void reset_positon(int new_default_position = 0);

    void first_axis_pos();

    void reset_speed_data();
    void reset_positon_data();
    void selcet_robomas_gear_ratio(uint8_t, uint8_t);
};

#endif
