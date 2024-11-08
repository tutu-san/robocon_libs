#pragma once
#ifndef CAN_HPP
#define CAN_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず
#include <cstdint>
#include <array>
#include <algorithm>
#include <span>
#define ENABLE_CAN 1

#if ENABLE_CAN

class can_transmit{
private:
    int hardware_fifo_freelevel=0;
    CAN_HandleTypeDef* can_handle;
	bool ext_id;
    std::array<uint32_t, 8> id_buff{};
    std::array<std::array<uint8_t, 8>, 8> data_buff{};
    std::array<uint8_t, 8> data_size_buff{};
	int input_num=0;
	int output_num=0;
public:
    can_transmit(CAN_HandleTypeDef* _can_handle, bool _ext_id = false) : can_handle(_can_handle), ext_id(_ext_id){}
    int transmit();
    void can_input_transmit_buffer(uint32_t can_id, std::span<uint8_t> can_data);
};

//old functions(一旦互換性として、後に削除予定)
void can_send(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id = false);

//can

//受信割り込みに関するコードをここに書くかどうか
//extern int can_send_num;

#endif

#endif
