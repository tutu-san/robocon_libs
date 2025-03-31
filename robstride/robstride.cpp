#include "robstride.hpp"
/*rotate*/
void robstride::current_rotate(float power_rate = 0.0f, float current_order = 0.0f, bool direct_control = false){
    union{
        float current_f;
        uint8_t current_u8[4];
    } target_current;
    
    clamp(power_rate, -1.0f, 1.0f);
    clamp(current_order, -90.0f, 90.0f);
    target_current.current_f = direct_control ? current_order : (power_rate * current_limit);

    uint32_t current_control_id = (0x12000000 + motor_id + (master_id<<8));
//    uint32_t current_control_id = 0x12000001;
    uint8_t send_data[8] = {0x06, 0x70, 0x00, 0x00, target_current.current_u8[0], target_current.current_u8[1], target_current.current_u8[2], target_current.current_u8[3]};
    for(int i = 0; i<8; i++){
    	_data[i] = send_data[i];
    }
    can_transmitter->can_input_transmit_buffer(current_control_id, send_data);
    return;
}

void robstride::positon_rotate(float target_position){
	uint32_t pram_write_id = (0x12000000 + motor_id + (master_id<<8));
	union{
	  float f;
	  uint8_t u[4];
	}Fu;
	Fu.f = target_position + default_positon;
	_target_data = Fu.f;
	uint8_t pp_target_data[8] = {0x16, 0x70, 0x00, 0x00, Fu.u[0], Fu.u[1], Fu.u[2], Fu.u[3]};
	can_transmitter->can_input_transmit_buffer(pram_write_id, pp_target_data);
}

void robstride::set_current_mode(){
    uint32_t mode_control_id = (0x12000000 + motor_id + (master_id<<8));;
    uint8_t send_data[5] = {0x05, 0x70, 0x00, 0x00, 0x03};
    
    can_transmitter->can_input_transmit_buffer(mode_control_id, send_data);
    return;
}

void robstride::set_positon_mode(){
	default_positon = 0.0f;
	positon_rotate(current_positon);
	default_positon = current_positon;
	uint32_t pram_write_id = (0x12000000 + motor_id + (master_id<<8));
	uint8_t set_pp_mode_data[] = {0x05, 0x70, 0x00, 0x00, 0x01};
	can_transmitter->can_input_transmit_buffer(pram_write_id, set_pp_mode_data);
}

void robstride::enable_motor(){
    uint32_t enable_id = (0x3000000 + motor_id + (master_id<<8));
    uint8_t send_data[8]{};
    
    can_transmitter->can_input_transmit_buffer(enable_id, send_data);
    return;
}

void robstride::stop_motor(){
	uint32_t enable_id = (0x4000000 + motor_id + (master_id<<8));
	uint8_t send_data[8]{};

	can_transmitter->can_input_transmit_buffer(enable_id, send_data);
	return;
}
/*encoder*/
void robstride::input_encoder_data(uint8_t(&rev_data)[8]){
	uint8_t encoder_data[8] = {rev_data[4], rev_data[5], rev_data[6], rev_data[7]};
	if(is_positon_requesting){
		current_positon = uint8_to_float(encoder_data);
		is_positon_requesting = false;
	}
}

float robstride::show_speed(){ //rad/s
    constexpr static float bit_16_divide = 1.0f/32768.0f;
    return speed_data * 15.0f * bit_16_divide;
}

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

float robstride::update_angle(int16_t angle,int16_t speed){
    bool angle_MSB = (angle > 0);
    bool old_angle_MSB = (old_angle > 0);

    if(old_angle_MSB == 1 && angle_MSB == 0 && speed > 0){
        turn_count++;
    }else if(old_angle_MSB == 0 && angle_MSB == 1 && speed < 0){
        turn_count--;
    }

    old_angle = angle;
    return angle_to_rad*(angle + turn_count*resolution);
}

void robstride::set_current_mode_gain(float _p_gain, float _i_gain){
//    p_gain = _p_gain;
//    i_gain = _i_gain;
//    uint32_t gain_write_id = (0x12000000 + motor_id + (master_id<<8));
//    uint32_t p_gain_bit = *reinterpret_cast<uint32_t*>(&p_gain);
//    uint32_t i_gain_bit = *reinterpret_cast<uint32_t*>(&i_gain);
//    uint8_t p_gain_write_data[8] = {0x10, 0x70, 0x00, 0x00, (p_gain_bit&0xff), ((p_gain_bit >> 8)&0xff), ((p_gain_bit >> 16)&0xff), ((p_gain_bit >> 24)&0xff)}; //little endian
//    uint8_t i_gain_write_data[8] = {0x11, 0x70, 0x00, 0x00, (i_gain_bit&0xff), ((i_gain_bit >> 8)&0xff), ((i_gain_bit >> 16)&0xff), ((i_gain_bit >> 24)&0xff)}; //little endian
//
//    can_transmitter->can_input_transmit_buffer(gain_write_id, p_gain_write_data);
//    can_transmitter->can_input_transmit_buffer(gain_write_id, i_gain_write_data);

}

void robstride::init(){
	;; //内容再検討
}

void robstride::over_write_pos(float new_data){
//    result_pos = new_data;
}

bool robstride::check_requesting_feedback(){
	//速度・位置共通としたい
	if(is_positon_requesting){return true;}
	return false;
}

void robstride::request_positon_data(){
	uint32_t req_feedback_id = (0x11000000 + motor_id + (master_id<<8));;
	uint8_t req_position_data[8] = {0x19, 0x70};
	can_transmitter->can_input_transmit_buffer(req_feedback_id, req_position_data);
	is_positon_requesting = true;
}

void robstride::motor_out(){
	is_positon_requesting = false;
}
