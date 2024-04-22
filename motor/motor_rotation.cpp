#include "motor_rotation.hpp"

//モータを回す
void motor_rotation::rotate(float motor_pwm){
	//motor_pwmのクランプ
	motor_pwm = clamp(motor_pwm, -65535.0f, 65535.0f);
    //正転と逆転を切り替える
	if(reverse_swtich == true){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_RESET : GPIO_PIN_SET));
	}else if(reverse_swtich == false){
		HAL_GPIO_WritePin(gpio_port, gpio_pin, (motor_pwm > 0.0f ? GPIO_PIN_SET : GPIO_PIN_RESET));
	}
	//PWM出力を更新する
	__HAL_TIM_SET_COMPARE(tim_handle, tim_channel, fabs(motor_pwm));
}