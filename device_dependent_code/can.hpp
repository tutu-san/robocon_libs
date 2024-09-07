#pragma once
#ifndef CAN_HPP
#define CAN_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず
#include <cstdint>
#define ENABLE_CAN

#ifdef ENABLE_CAN
//define can_send_buffer
struct can_send_buffer{
    uint32_t id[8]{};
    uint8_t data[8][8]{};
    int input_num=0;
    int output_num=0;
};

//can_send_buffer
extern can_send_buffer can1_send_buffer;
extern can_send_buffer can2_send_buffer;
//functions
void can_input_transmit_buffer(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8]);
void can_transmit(void* _can_handle);
//old functions
void can_send(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id = false);

//can

//受信割り込みに関するコードをここに書くかどうか
//extern int can_send_num;

#endif

#endif
