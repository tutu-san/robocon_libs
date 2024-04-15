#pragma once
#ifndef TOOLS
#define TOOLS

#include <cmath>
#include <cstdint>
//クランプ
template<typename T>
void clamp(T&original_data, T max_value, T min_value){
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
//型変更系
//uint8_t -> float
float uint8_to_float(uint8_t(&uint_datas)[8]);
//uint8_t -> uint16_t
int uint8_to_int(uint8_t input_data_high, uint8_t input_data_low);
#endif