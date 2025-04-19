#include "vesc.hpp"

void vesc_rotation::duty_rotate(float power_ratio){
    constexpr float vesc_max_value = 100000.0f;
    // power_ratio *= -1.0f;
    clamp(power_ratio, -1.0f, 1.0f);
    last_input_data = power_ratio;
    int32_t pwm_value = power_ratio * vesc_max_value;
    uint8_t converted_pwm_value_data[4]{(pwm_value>>24)&0xff, (pwm_value>>16)&0xff, (pwm_value>>8), pwm_value&0xff};
    can_transmitter->can_input_transmit_buffer(motor_id, converted_pwm_value_data);
}

void vesc_rotation::current_rotate(float power_ratio){
    //Command Relative Current
    uint32_t send_id = motor_id + (0xA<<8);
    // power_ratio *= -1.0f;
    clamp(power_ratio, -1.0f, 1.0f);
    last_input_data = power_ratio;
    int32_t ratio_data = power_ratio * 100000;
    uint8_t send_data[4]{(ratio_data>>24)&0xff, (ratio_data>>16)&0xff, (ratio_data>>8), ratio_data&0xff};
    can_transmitter->can_input_transmit_buffer(send_id, send_data);
}

void vesc_rotation::speed_rotate(float target_speed){
    uint32_t send_id = motor_id + (0x3<<8);
    int32_t rpm_data = static_cast<int32_t>(target_speed);
    uint8_t send_data[4]{};
    std::memcpy(send_data, &rpm_data, 4); 
    can_transmitter->can_input_transmit_buffer(send_id, send_data);
}

void vesc_rotation::position_rotate(float target_positon){
    uint32_t send_id = motor_id + (0x4<<8);
    int32_t pos_data = static_cast<int32_t>(target_positon);
    uint8_t send_data[4]{};
    std::memcpy(send_data, &pos_data, 4);
    can_transmitter->can_input_transmit_buffer(send_id, send_data);
}
