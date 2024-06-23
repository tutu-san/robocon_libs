#include "robomas_rotation.hpp"

void robomas_rotation::input_rotation_data(int motor_number, float input_power_ratio){
	if(motor_number >= 4) return; //範囲外アクセス防止
	clamp(input_power_ratio, -1.0f, 1.0f);
	float input_pwm_data = input_power_ratio * 14000.0f;
	clamp(input_pwm_data, -14000.0f, 14000.0f);
	robomas_pwm_data[motor_number] = input_pwm_data;
}

void robomas_rotation::rotate(){
	uint8_t robomas_send_data[8] = {0};
	convert_to_send_data(robomas_pwm_data, robomas_send_data);
	can_send(can_handle, robomas_can_id, robomas_send_data);
}

void robomas_rotation::convert_to_send_data(const float(&robomas_pwm_data)[4], uint8_t(&robomas_send_data)[8]){
	int16_t robomas_int16_pwm_data[4]; //float to int
	robomas_int16_pwm_data[0] = (int16_t)robomas_pwm_data[0];
	robomas_int16_pwm_data[1] = (int16_t)robomas_pwm_data[1];
	robomas_int16_pwm_data[2] = (int16_t)robomas_pwm_data[2];
	robomas_int16_pwm_data[3] = (int16_t)robomas_pwm_data[3];

	for(int i=0; i<4; i++){
		clamp(robomas_int16_pwm_data[i], (int16_t)-15000, (int16_t)15000);
	}

	robomas_send_data[0] = (uint16_t)robomas_int16_pwm_data[0] >> 8;
	robomas_send_data[1] = (uint16_t)robomas_int16_pwm_data[0] & 0xff;
	robomas_send_data[2] = (uint16_t)robomas_int16_pwm_data[1] >> 8;
	robomas_send_data[3] = (uint16_t)robomas_int16_pwm_data[1] & 0xff;
	robomas_send_data[4] = (uint16_t)robomas_int16_pwm_data[2] >> 8;
	robomas_send_data[5] = (uint16_t)robomas_int16_pwm_data[2] & 0xff;
	robomas_send_data[6] = (uint16_t)robomas_int16_pwm_data[3] >> 8;
	robomas_send_data[7] = (uint16_t)robomas_int16_pwm_data[3] & 0xff;
}
