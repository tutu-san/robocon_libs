#include "robstride.hpp"

void robstride::current_rotate(float power_rate, float current_order, bool direct_control){
    clamp(power_rate, -1.0f, 1.0f);
    clamp(current_order, -90.0f, 90.0f);
    float target_current = direct_control ? current_order : (power_rate * current_limit);

    uint32_t current_control_id = (0x12000000 + motor_id + (master_id<<8));
    uint8_t send_data[8] = {0x06, 0x70, 0x00, 0x00};
    std::memcpy(&send_data[4], &target_current, sizeof(target_current));
    can_transmitter->can_input_transmit_buffer(current_control_id, send_data);
}

void robstride::positon_rotate(float target_position){
    clamp(target_position, static_cast<float>(-M_PI), static_cast<float>(M_PI));
    uint32_t pram_write_id = (0x12000000 + motor_id + (master_id<<8));
    float pos = (-target_position) + default_positon;
    _target_data = pos;
    uint8_t pp_target_data[8] = {0x16, 0x70, 0x00, 0x00};
    std::memcpy(&pp_target_data[4], &pos, sizeof(pos));
    can_transmitter->can_input_transmit_buffer(pram_write_id, pp_target_data);
}

void robstride::set_current_mode(){
    uint32_t mode_control_id = (0x12000000 + motor_id + (master_id<<8));
    uint8_t send_data[5] = {0x05, 0x70, 0x00, 0x00, 0x03};
    can_transmitter->can_input_transmit_buffer(mode_control_id, send_data);
}

void robstride::position_mode_spd_lim(float limit){
    uint32_t mode_control_id = (0x12000000 + motor_id + (master_id<<8));
    uint8_t send_data[8] = {0x24, 0x70, 0x00, 0x00};
    std::memcpy(&send_data[4], &limit, 4);
    can_transmitter->can_input_transmit_buffer(mode_control_id, send_data);
}

void robstride::set_positon_mode(){
    float _tmp_default_position = default_positon;
    default_positon = 0.0f;
    positon_rotate(current_positon);
    default_positon = _tmp_default_position;
    uint32_t pram_write_id = (0x12000000 + motor_id + (master_id<<8));
    uint8_t set_pp_mode_data[] = {0x05, 0x70, 0x00, 0x00, 0x01};
    can_transmitter->can_input_transmit_buffer(pram_write_id, set_pp_mode_data);
}

void robstride::enable_motor(){
    is_motor_rebooted = true;
    uint32_t enable_id = (0x3000000 + motor_id + (master_id<<8));
    uint8_t send_data[8]{};
    can_transmitter->can_input_transmit_buffer(enable_id, send_data);
}

void robstride::stop_motor(){
    uint32_t enable_id = (0x4000000 + motor_id + (master_id<<8));
    uint8_t send_data[8]{};
    can_transmitter->can_input_transmit_buffer(enable_id, send_data);
}

inline float normalize_angle(float angle){
    while(angle < 0.0f) angle += 2 * M_PI;
    while(angle >= 2 * M_PI) angle -= 2 * M_PI;
    return angle;
}

void robstride::input_encoder_data(uint8_t(&rev_data)[8]){
    uint8_t encoder_data[8] = {rev_data[4], rev_data[5], rev_data[6], rev_data[7]};
    if(is_positon_requesting){
        float new_position = uint8_to_float(encoder_data);

        if(is_motor_rebooted){
            if((new_position > (default_positon + M_PI))/* && (stored_position_before_power_down < default_positon)*/){
                default_positon += (M_PI * 2.0f);
            }else if(((default_positon - M_PI) > new_position)/* && (stored_position_before_power_down > default_positon)*/){
                default_positon -= (M_PI * 2.0f);
            }
            is_motor_rebooted = 0;
        }

        if(fabs(new_position - current_positon) > 1.0f){
            big_change_limiter++;
            if(big_change_limiter > 10){
                current_positon = new_position;
            }
        }else{
            big_change_limiter = 0;
            current_positon = new_position;
        }
        is_positon_requesting = false;
        _is_position_requesting_debug = 0;
    }
}

float robstride::show_speed(){ }

float robstride::show_angle(){
    return current_positon - default_positon;
}

void robstride::set_default_position(float new_position, bool abs_mode){
    if(abs_mode){
        default_positon = new_position;
    }else{
        default_positon = current_positon + new_position;
    }
}

float robstride::update_angle(int16_t angle,int16_t speed){ }

void robstride::set_current_mode_gain(float _p_gain, float _i_gain){ }

void robstride::init(){ }

void robstride::over_write_pos(float new_data){ }

bool robstride::check_requesting_feedback(){
    if(is_positon_requesting){return true;}
    return false;
}

void robstride::request_positon_data(){
    uint32_t req_feedback_id = (0x11000000 + motor_id + (master_id<<8));
    uint8_t req_position_data[8] = {0x19, 0x70};
    can_transmitter->can_input_transmit_buffer(req_feedback_id, req_position_data);
    is_positon_requesting = true;
    _is_position_requesting_debug = 1;
}

void robstride::motor_out(){
    is_positon_requesting = false;
    _is_position_requesting_debug = 0;
}

void robstride::current_position_power_down_process(){
    stored_position_before_power_down = current_positon;
}
