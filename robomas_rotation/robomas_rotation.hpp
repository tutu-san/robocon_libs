/**
 * @file robomas_rotation.hpp
 * @brief robomas_rotation header file
 * @details ロボマスモーターの回転指令を行うクラス、メソッドの実装は robomas_rotation.cppを参照されたい
 */
#pragma once
#ifndef ROBOMAS_ROTATION
#define ROBOMAS_ROTATION

#include <cstdint>
#include <algorithm>
#include "stm32h7xx_hal.h" //stm32各チップに対応した、halライブラリをインクルードすること(現在は h743で仮置き)
#include "../tools/tools.hpp"

class robomas_rotation{
private:
    constexpr static uint32_t robomas_can_tx_id = 0x200; //ロボマスモータ送信id(No. 1~4 0x200, 5~8 0x1FF)
    FDCAN_HandleTypeDef* fdcan_handle; //canfd handle (canの場合は変更)
    FDCAN_TxHeaderTypeDef tx_header; //canfd tx header(canの場合は変更)
    void convert_to_send_data(const float(&)[4], uint8_t(&)[8]);
    void can_send(uint8_t(&)[8]);
    float robomas_pwm_data[4] = {0.0f};
public:
    robomas_rotation(FDCAN_HandleTypeDef* _fdcan_handle) : fdcan_handle(_fdcan_handle)
    {
        //canの送信ヘッダの初期設定(stm32 canfd向け stm32 canの場合は変更が必要)
        tx_header.Identifier = robomas_can_tx_id;
        tx_header.IdType = FDCAN_STANDARD_ID;
        tx_header.TxFrameType = FDCAN_DATA_FRAME;
        tx_header.DataLength = FDCAN_DLC_BYTES_8;
        tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
        tx_header.BitRateSwitch = FDCAN_BRS_OFF;
        tx_header.FDFormat = FDCAN_CLASSIC_CAN;
        tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
        tx_header.MessageMarker = 0;    
    }
    void rotate();
    void input_rotation_data(int, float);
};
#endif