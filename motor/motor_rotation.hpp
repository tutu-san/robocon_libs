/**
 * @file motor_rotation.hpp
 * @brief motor_rotation header file
 * @details DCモータの回転指令を送るクラス、メソッドの実装は motor_rotation.cppを参照されたい
 */
#pragma once
#ifndef MOTOR_ROTATION
#define MOTOR_ROTATION

#include "stm32f4xx_hal.h" //仮置き(for f446re) 適宜各stm32用のhalライブラリをインクルードすること
#include "../tools/tools.hpp"
#include <cmath>

class motor_rotation{
private:
    GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
protected:
    TIM_HandleTypeDef* tim_handle;
	uint32_t tim_channel;
    bool reverse_swtich; //正転と逆転を切り替える
public:
    motor_rotation(GPIO_TypeDef* _gpio_port, uint16_t _gpio_pin, TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel, bool _reverse_swtich):
    gpio_port(_gpio_port),gpio_pin(_gpio_pin),tim_handle(_tim_handle), tim_channel(_tim_channel), reverse_swtich(_reverse_swtich){}
    virtual void rotate(float);
};

class dcmd_rotation : motor_rotation {
private:
	TIM_HandleTypeDef* tim_handle_inverse;
	uint32_t tim_channel_inverse;
public:
    dcmd_rotation(TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel, TIM_HandleTypeDef* _tim_handle_inverse, uint32_t _tim_channel_inverse, bool _reverse_swtich):
	motor_rotation(nullptr, 0, _tim_handle, _tim_channel, _reverse_swtich), tim_handle_inverse(_tim_handle_inverse), tim_channel_inverse(_tim_channel_inverse){}
    void rotate(float) override;
};
#endif