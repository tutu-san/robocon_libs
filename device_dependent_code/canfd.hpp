#pragma once
#ifndef CANFD_HPP
#define CANFD_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず

void can_send(FDCAN_Handle_Typedef* canfd_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id);

//受信割り込みに関するコードをここに書くかどうか

#endif