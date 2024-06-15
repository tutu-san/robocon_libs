#pragma once
#ifndef CAN_HPP
#define CAN_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず

#define ENABLE_CAN

#ifdef ENABLE_CAN
void can_send(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id = false);

//受信割り込みに関するコードをここに書くかどうか
#endif

#endif
