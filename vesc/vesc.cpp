#include "vesc.hpp"

void vesc_rotation::rotate(float power_ratio){
    constexpr float vesc_max_value = 10000.0f;
    clamp(power_ratio, -1.0f, 1.0f);
    int32_t pwm_value = power_ratio * vesc_max_value;
    uint8_t converted_pwm_value_data[4] = {pwm_value >> 24, pwm_value >> 16, pwm_value >> 8, pwm_value & 0xff};
    can_transmitter->can_input_transmit_buffer(motor_id, converted_pwm_value_data);
}
