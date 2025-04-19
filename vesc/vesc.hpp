#pragma once
#ifndef VESC_HPP_
#define VESC_HPP_
//robomas_rotaionとほぼ同じなので、継承を使うべきだとは思ったりした
#include "device_dependent_code/can.hpp"
#include "device_dependent_code/canfd.hpp"

#include <cstdint>
#include <algorithm>
#include <cstring>
#include "../tools/tools.hpp"
#include "../robomas_rotation/robomas_rotation.hpp"

class vesc_rotation{
private:
    can_transmit* can_transmitter;
    uint32_t motor_id;
    float last_input_data=0.0f; //勝手に止まってしまうので
public:
    vesc_rotation(can_transmit* _can_transmitter, uint32_t _motor_id)
    : can_transmitter(_can_transmitter), motor_id(_motor_id){}
    void duty_rotate(float power_ratio);
    void current_rotate(float power_ratio);
    void speed_rotate(float target_speed);
    void position_rotate(float target_position);
    float input_last_input_data(){return last_input_data;}
};
#endif
