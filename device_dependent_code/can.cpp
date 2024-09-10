#include "can.hpp"

#ifdef ENABLE_CAN
//int can_send_num;
//input can_data
void can_transmit::can_input_transmit_buffer(uint32_t can_id, uint8_t(&send_data)[8]){
    id_buff[input_num] = can_id;
    for(int i=0; i<8; i++){
        data_buff[input_num][i] = send_data[i];
    }
    //リングバッファを実現
    input_num++;
    if(input_num >= 8)input_num = 0;
    return;
}

//can transmit_extid
void can_transmit::transmit(){
    CAN_TxHeaderTypeDef tx_header;
    uint32_t mailbox;
    //現在のハードウェアバッファの空き容量を問い合わせる
    hardware_fifo_freelevel = HAL_CAN_GetTxMailboxesFreeLevel(can_handle);
    if(hardware_fifo_freelevel < 1){
        //バッファが空きでない場合は青ランプ点灯の上、何もしない(送信成功まで点灯)
        HAL_GPIO_WritePin(LEDB_GPIO_Port, LEDB_Pin, GPIO_PIN_SET);
        return; 
    }
    //can transmit
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 8;
    tx_header.TransmitGlobalTime = DISABLE;
    if(ext_id){
        tx_header.IDE = CAN_ID_EXT;
        tx_header.ExtId = id_buff[output_num];
    }else{
        tx_header.IDE = CAN_ID_STD;
        tx_header.StdId = id_buff[output_num];
    }
    if(id_buff[output_num] == 0){
        output_num++;
        if(output_num >= 8) output_num = 0;
        return; //id_buff=0は、データ無しと判断、送信しない(実際は、cccのnoneに該当)
    }
    HAL_CAN_AddTxMessage(can_handle, &tx_header, data_buff[output_num], &mailbox);
    //データクリーニング(送信後のデータの多重送信を防ぐ)
    for(int i = 0; i<8; i++){
        data_buff[output_num][i] = 0;
    }
    id_buff[output_num] = 0;
    //送信番号更新
    output_num++;
    if(output_num >= 8) output_num = 0;
    HAL_GPIO_WritePin(LEDB_GPIO_Port, LEDB_Pin, GPIO_PIN_RESET);
    return;
}
#endif
#ifdef OLD_CAN
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