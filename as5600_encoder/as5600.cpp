#include "as5600.hpp"
void as5600_tool::request_encoder_data(){
    HAL_GPIO_WritePin(slave_selecter.port, slave_selecter.pin, GPIO_PIN_SET);
    rev_mode = true;
    HAL_I2C_Mem_Read_IT(i2c_handle, as5600_i2c_id, static_cast<uint16_t>(as5600_angle_reg), I2C_MEMADD_SIZE_8BIT, rev_buffer_i2c, 2);
}

void as5600_tool::receive_encoder_data(){
    if(!rev_mode) return;
    rev_angle_data = ((rev_buffer_i2c[0]&0xff)<<8) | rev_buffer_i2c[1]; //0~4095
    rev_delta_angle = rev_angle_data - last_rev_angle_data;
    if(rev_delta_angle > 2048){
        rev_delta_angle -= 4096;
        turn_count++;
    }else if(rev_delta_angle < -2048){
        rev_delta_angle += 4096;
        turn_count--;
    }
    ruiseki_angle_data += rev_delta_angle;
    last_rev_angle_data = rev_angle_data;
    HAL_GPIO_WritePin(slave_selecter.port, slave_selecter.pin, GPIO_PIN_RESET);
    rev_mode = false;
}

float as5600_tool::show_speed(){
    float rad_per_sec = deg_to_rad(rev_delta_angle / bit12_value) / delta_t;
    return rad_per_sec;
}

float as5600_tool::show_angle(){
    float rad = deg_to_rad(ruiseki_angle_data / bit12_value);
    _angle_data = rad;
    return rad;
}

float as5600_tool::show_raw_angle(){
    //絶対座標ってなんだ？
    float rad = deg_to_rad(rev_angle_data / bit12_value);
    return rad;
}

int as5600_tool::show_turn_count(){
    return turn_count;
}

void as5600_tool::reset_ruiseki_angle(){
    ruiseki_angle_data = 0;
}
