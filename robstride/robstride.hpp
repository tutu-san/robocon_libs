#pragma once
#ifndef ROBSTRIDE_HPP_
#define ROBSTRIDE_HPP_

#include <cmath>
#include <cstdint>
#include "stm32f4xx_hal.h"
#include "../tools/tools.hpp"
#include "../device_dependent_code/can.hpp"

class robstride{
    //can
    can_transmit* can_transmitter;
    const uint8_t master_id = 0x00; //0xFD
    const uint8_t motor_id = 0x00; //0x7F
    //raw_data, tmp_data
    int16_t angle_data = 0;
    int16_t speed_data = 0;
    int16_t touque_data = 0;
    
    //angle_data
    constexpr static size_t resolution_bit = 16;
    constexpr static int resolution = 1<<resolution_bit;
    constexpr static float angle_to_rad = 8*M_PI/(float)resolution;
    int32_t turn_count = 0;
    int16_t old_angle = 0;
    float ruisekiwa = 0.0f;
    float last_data = 0.0f;
    float result_pos = 0.0f;
    float update_angle(int16_t angle,int16_t speed);

    //new_encoder
    float current_positon = 0.0f;
    bool is_positon_requesting = false;
    float default_positon = 0.0f;

    //limit
    float current_limit = 2.0f;

    //current gain
    float p_gain = 0.0f, i_gain = 0.0f;
public:
    //コンストラクタ
    robstride(can_transmit* _can_transmitter, uint8_t _master_id, uint8_t _motor_id) 
    : can_transmitter(_can_transmitter), master_id(_master_id), motor_id(_motor_id){}
    //init
    void init();
    //can
    void input_encoder_data(uint8_t(&)[8]);
    bool check_requesting_feedback();
    void motor_out();
    //関数ポインタ使えそうかも？
    void request_positon_data();

    //rotation
	void current_rotate(float, float, bool);
	void positon_rotate(float);
	//speed
	float show_speed();
    //angle
    float show_angle();
    void set_default_position(float);
    //mode_change
    void set_current_mode();
    void set_positon_mode();
    void enable_motor();
    void stop_motor();

    void set_current_mode_gain(float, float);

    //
    uint8_t show_mcu_memory_motor_id(){return motor_id;}

    void over_write_pos(float);
    float _target_data = 0.0f;

    uint8_t _data[8]{};
};
#endif
