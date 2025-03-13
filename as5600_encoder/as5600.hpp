#pragma once
#ifndef AS5600_HPP_
#define AS5600_HPP_

#include "stm32f4xx_hal.h"
#include <cstdint>

class as5600_tool{
private:
    I2C_HandleTypeDef* i2c_handle;
    constexpr static uint8_t as5600_i2c_id = 0x36<<1;
    constexpr static uint8_t as5600_angle_reg = 0x0e;
    uint16_t rev_angle_data;
public:
    as5600_tool(I2C_HandleTypeDef* _i2c_handle)
    :i2c_handle(_i2c_handle){}
    uint8_t rev_buffer_i2c[5];
    void request_encoder_data();
    void receive_encoder_data();
};

#endif