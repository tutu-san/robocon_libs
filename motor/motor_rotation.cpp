#include "motor_rotation.hpp"

void motor_rotation::rotate(float motor_pwm){
	//motor_pwmのクランプ
	clamp(motor_pwm, -1.0f, 1.0f);
	__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm) * (tim_handle->Init.Period));
	return;
}

//モータを回す
void ucs3_rotation::rotate(float motor_pwm){
	//motor_pwmのクランプ
	clamp(motor_pwm, -1.0f, 1.0f);
    //正転と逆転を切り替える
	if(reverse_swtich^(motor_pwm>0.0f)){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_RESET);
	}else{
		HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);
	}
	//PWM出力を更新する
	__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm) * (tim_handle->Init.Period));
}

void dcmd_rotation::rotate(float motor_pwm){
	clamp(motor_pwm, -1.0f, 1.0f);
	bool rotate_dir = motor_pwm > 0.0f; //正転か逆転かを判断(入力値より)
	//回転させる
	if(rotate_dir ^ reverse_swtich){
		__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm) * (tim_handle->Init.Period));
		__HAL_TIM_SET_COMPARE(tim_handle_inverse, tim_channel_inverse, 0);
	}else{
		__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, 0);
		__HAL_TIM_SET_COMPARE(tim_handle_inverse, tim_channel_inverse, fabs(motor_pwm) * (tim_handle->Init.Period));
	}
}