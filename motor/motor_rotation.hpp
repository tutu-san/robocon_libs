/**
 * @file motor_rotation.hpp
 * @brief motor_rotation header file
 * @details DCモータの回転指令を送るクラス、メソッドの実装は motor_rotation.cppを参照されたい
 * @attention Note: HAL_TIM_PWM_Start()は、hal_init()後に実行したほうが良い(経験則)ので、別途実行すること
 */
#pragma once
#ifndef MOTOR_ROTATION
#define MOTOR_ROTATION

#include "main.h" //仮置き(for f446re) 適宜各stm32用のhalライブラリをインクルードすること
#include "../tools/tools.hpp"
#include <cmath>

class motor_rotation{
protected:
    TIM_HandleTypeDef* tim_handle;
    uint32_t tim_channel;
public:
    motor_rotation(TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel):
    tim_handle(_tim_handle), tim_channel(_tim_channel){}
    virtual void rotate(float);
};

//1つのPWM入力・1つの方向設定入力で動かすモータードライバー向け
class ucs3_rotation : public motor_rotation{
protected:
    GPIO_TypeDef* gpio_port;
	uint16_t gpio_pin;
    bool reverse_swtich; //正転と逆転を切り替える
public:
    ucs3_rotation(GPIO_TypeDef* _gpio_port, uint16_t _gpio_pin, TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel, bool _reverse_swtich):
    motor_rotation(_tim_handle, _tim_channel),gpio_port(_gpio_port), gpio_pin(_gpio_pin), reverse_swtich(_reverse_swtich){}
    void rotate(float) override;
};

//1つのPWM入力・2つの方向設定入力で動かすモータードライバー向け
//今度作る(VNH rotation)

//2つのPWM入力だけで動かすモータードライバー向け
class dcmd_rotation : ucs3_rotation {
private:
	TIM_HandleTypeDef* tim_handle_inverse;
	uint32_t tim_channel_inverse;
public:
    dcmd_rotation(TIM_HandleTypeDef* _tim_handle, uint32_t _tim_channel, TIM_HandleTypeDef* _tim_handle_inverse, uint32_t _tim_channel_inverse, bool _reverse_swtich):
    ucs3_rotation(nullptr, 0, _tim_handle, _tim_channel, _reverse_swtich), tim_handle_inverse(_tim_handle_inverse), tim_channel_inverse(_tim_channel_inverse){}
    void rotate(float) override;
};
#endif
