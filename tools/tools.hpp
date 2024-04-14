#pragma once
#ifndef TOOLS
#define TOOLS
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

//型変更系
//uint8_t -> float

//uint8_t -> uint16_t

#endif