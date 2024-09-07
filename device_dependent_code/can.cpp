#include "can.hpp"

#ifdef ENABLE_CAN
//int can_send_num;
//struct can_send_fuffer
can_send_buffer can1_send_buffer;
can_send_buffer can2_send_buffer;
//input can_data
void can_input_transmit_buffer(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8]){
    CAN_HandleTypeDef* can_handle = (CAN_HandleTypeDef*)_can_handle;
    if(can_handle == &hcan1){
        ;;
        can1_send_buffer.id[can1_send_buffer.input_num] = can_id;
        for(int i=0; i<8; i++){
            can1_send_buffer.data[can1_send_buffer.input_num][i] = send_data[i];
        }
        can1_send_buffer.input_num++;
        if(can1_send_buffer.input_num >= 8) can1_send_buffer.input_num = 0;
    }else if(can_handle == &hcan2){
        ;;
        can2_send_buffer.id[can2_send_buffer.input_num] = can_id;
        for(int i=0; i<8; i++){
            can2_send_buffer.data[can2_send_buffer.input_num][i] = send_data[i];
        }
        can2_send_buffer.input_num++;
        if(can2_send_buffer.input_num >= 8) can2_send_buffer.input_num = 0;
    }
}

//can transmit
void can_transmit(void* _can_handle){
    CAN_HandleTypeDef* can_handle = (CAN_HandleTypeDef*)_can_handle;
    //現在のハードウェアバッファの空き容量を問い合わせる
    if(HAL_CAN_GetTxMailboxesFreeLevel(can_handle) < 1)return; //バッファが空きでない場合は何もしない
    if(can_handle == &hcan1){
        
    }else if(can_handle == &hcan2){

    }
}

//互換性を保つため、一時的に保管(再書き込みするため)
void can_send(void* _can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id){
	CAN_HandleTypeDef* can_handle = (CAN_HandleTypeDef*)_can_handle;
	CAN_TxHeaderTypeDef tx_header;
    uint32_t mailbox;

    //header settings
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 8;
    tx_header.TransmitGlobalTime = DISABLE;
    if(extended_id){
        tx_header.IDE = CAN_ID_EXT;
        tx_header.ExtId = can_id;
    }else{
        tx_header.IDE = CAN_ID_STD;
        tx_header.StdId = can_id;
    }
//    while(HAL_CAN_GetTxMailboxesFreeLevel(can_handle) < 1){
//    	HAL_GPIO_WritePin(LEDB_GPIO_Port, LEDB_Pin, GPIO_PIN_SET);
//    }
    if(HAL_CAN_GetTxMailboxesFreeLevel(can_handle) < 1){
		HAL_GPIO_WritePin(LEDB_GPIO_Port, LEDB_Pin, GPIO_PIN_SET);
		return;
	}
    HAL_GPIO_WritePin(LEDB_GPIO_Port, LEDB_Pin, GPIO_PIN_RESET);
    HAL_CAN_AddTxMessage(can_handle, &tx_header, send_data, &mailbox);
//    if(can_handle->Instance == CAN1) can_send_num++;
//    can_send_num++;
    return;
}
#endif
