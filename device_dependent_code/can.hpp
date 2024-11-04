#pragma once
#ifndef CAN_HPP
#define CAN_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず
#include <cstdint>
#define ENABLE_CAN 1

#if ENABLE_CAN

class can_transmit{
private:
    int hardware_fifo_freelevel=0;
    CAN_HandleTypeDef* can_handle;
	bool ext_id;
	uint32_t id_buff[8]{};
	uint8_t data_buff[8][8]{};
	int input_num=0;
	int output_num=0;
public:
    can_transmit(CAN_HandleTypeDef* _can_handle, bool _ext_id = false) : can_handle(_can_handle), ext_id(_ext_id){}
    void transmit();
    void can_input_transmit_buffer(uint32_t can_id, uint8_t(&send_data)[8]);
};

//old functions(一旦互換性として、後に削除予定)
void can_send(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id = false);

//can

//受信割り込みに関するコードをここに書くかどうか
//extern int can_send_num;

#endif

#endif
