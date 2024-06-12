#include "motor_rotation.hpp"

void motor_rotation::rotate(){
	return;
}

//モータを回す
void ucs3_rotation::rotate(float motor_pwm){
	//motor_pwmのクランプ
	clamp(motor_pwm, -65535.0f, 65535.0f);
    //正転と逆転を切り替える
	if(reverse_swtich == true){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_RESET : GPIO_PIN_SET));
	}else if(reverse_swtich == false){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_SET : GPIO_PIN_RESET));
	}
	//PWM出力を更新する
	__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm));
}

void dcmd_rotation::rotate(float motor_pwm){
	clamp(motor_pwm, -1.0f, 1.0f);
	bool rotate_dir = motor_pwm > 0.0f; //正転か逆転かを判断(入力値より)
	if(reverse_swtich == true){ //Reverse_swtich によって、回転方向を逆転
        rotate_dir = !rotate_dir;
    }
	//回転させる
	if(rotate_dir){
		__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm) * (tim_handle->Init.Period));
		__HAL_TIM_SET_COMPARE(tim_handle_inverse, tim_channel_inverse, 0);
	}else{
		__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, 0);
		__HAL_TIM_SET_COMPARE(tim_handle_inverse, tim_channel_inverse, fabs(motor_pwm) * (tim_handle->Init.Period));
	}
}