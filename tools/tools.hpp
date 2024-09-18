#pragma once
#ifndef TOOLS
#define TOOLS

#include <cmath>
#include <cstdint>
#include <bit>
#include <array>
//クランプ
template<typename T>
void clamp(T&original_data, T min_value, T max_value){
    if(max_value < original_data){
        original_data = max_value;
        return;    
    }else if(min_value > original_data){
        original_data = min_value;
        return;
    }else{
        return;
    }
    return;
}
//単位変換系
// rad/s -> rpm
float rad_per_sec_to_rpm(float rad_par_sec_input);
//rad -> deg
float rad_to_degree(float rad);
//deg -> robomas_angle
float degree_to_robomas_encoder_angle(float target_deg, float now_pos, float gear_ratio);
//型変更系
//uint8_t -> float
float uint8_to_float(uint8_t(&uint_datas)[8]);
//uint8_t -> uint16_t
int uint8_to_int(uint8_t input_data_high, uint8_t input_data_low);
//uint8_t -> uint64_t
uint64_t uint8_to_uint64(uint8_t(&input_data)[8]);
//float -> uint8_t
void float_to_uint8(float input, uint8_t(&)[8]);
//uint16_t -> uint8_t
void uint16_to_uint8(uint16_t input, uint8_t(&)[8]);
#endif