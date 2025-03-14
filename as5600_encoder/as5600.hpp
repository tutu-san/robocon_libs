#pragma once
#ifndef AS5600_HPP_
#define AS5600_HPP_

#include "stm32f4xx_hal.h"
#include <cstdint>
#include "../tools/tools.hpp"

typedef struct as5600_selecter_struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} as5600_selecter_t;

class as5600_tool{
private:
    I2C_HandleTypeDef* i2c_handle;
    as5600_selecter_t&slave_selecter;
    constexpr static uint8_t as5600_i2c_id = 0x36<<1;
    constexpr static uint8_t as5600_angle_reg = 0x0e;
    constexpr static float bit12_value = 4096.0f;
    const float delta_t;
    uint16_t rev_angle_data = 0;
    uint16_t last_rev_angle_data = 0;
    int16_t turn_count = 0;
    int64_t ruiseki_angle_data = 0;
    int16_t rev_delta_angle = 0;
    bool rev_mode = false;
public:
    as5600_tool(I2C_HandleTypeDef* _i2c_handle, as5600_selecter_t&_slave_selecter, float _delta_t)
    :i2c_handle(_i2c_handle), slave_selecter(_slave_selecter), delta_t(_delta_t){}
    uint8_t rev_buffer_i2c[5];
    bool turn_direction_reverse = false;
    void request_encoder_data();
    void receive_encoder_data();
    float show_speed();
    float show_angle();
    float show_raw_angle();
    int show_turn_count();
    void reset_ruiseki_angle();
};

#endif
