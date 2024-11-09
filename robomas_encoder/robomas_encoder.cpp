#include "robomas_encoder.hpp"

void robomas_encoder::input_encoder_data(uint8_t robomas_encoder_data[8]){
    //データを入れるってこと
    robomas_input_rpm_high = robomas_encoder_data[2];
    robomas_input_rpm_low = robomas_encoder_data[3];
    robomas_input_pos_high = robomas_encoder_data[0];
    robomas_input_pos_low = robomas_encoder_data[1];
    robomas_input_current_high = robomas_encoder_data[4];
    robomas_input_current_low = robomas_encoder_data[5];
    angle_data = (robomas_input_pos_high << 8 | robomas_input_pos_low) - 4095;
    speed_data = robomas_input_rpm_high << 8 | robomas_input_rpm_low;
    current_data = robomas_input_current_high << 8 | robomas_input_current_low; //なんかちがう
}

float robomas_encoder::show_rpm(){
    //上位,下位ビットの統合
    uint16_t unsigned_robomas_rpm_data = robomas_input_rpm_high << 8 | robomas_input_rpm_low;

    const int16_t signed_robomas_rpm_data = unsigned_robomas_rpm_data;
    const float axis_robomas_rpm_data = static_cast<float>(signed_robomas_rpm_data) / motor_gear_ratio; //ギア比で割っている

    //debug
    debug_robomas_rpm = axis_robomas_rpm_data;
    //おしまい
    return axis_robomas_rpm_data;
}

float robomas_encoder::show_pos(){
	ruisekiwa = update_angle(angle_data, speed_data);
	result_pos += (ruisekiwa - last_data);
	last_data = ruisekiwa;
	return result_pos;
}

void robomas_encoder::first_axis_pos(){
	ruisekiwa = update_angle(angle_data, speed_data);
	last_data = ruisekiwa;
	return;
}

void robomas_encoder::reset_positon(int new_default_position){
	default_position = new_default_position;
}

void robomas_encoder::change_motor_type(robomas_motor_type_enum motor_type){
	switch(motor_type){
		case robomas_motor_type_enum::M2006:
			motor_gear_ratio = 36.0f;
			break;
		case robomas_motor_type_enum::M3508:
			motor_gear_ratio = 19.2f; /* 3591.0f / 187.0f  を近似*/
			break;
	}
}

//from taichi_encoder
float robomas_encoder::update_angle(int16_t angle,int16_t speed){
//    angle = angle&(resolution-1);//一応マスク
//    int angle_MSB = (angle>>(resolution_bit-1))&0b1;
//    int old_angle_MSB = (old_angle>>(resolution_bit-1))&0b1;
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

void robomas_encoder::reset_speed_data(){
    robomas_input_rpm_high = 0;
	robomas_input_rpm_low = 0;
}

void robomas_encoder::reset_positon_data(){
    robomas_input_pos_high = 0;
	robomas_input_pos_low = 0;
}