#include "can.hpp"

#ifdef ENABLE_CAN
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

    HAL_CAN_AddTxMessage(can_handle, &tx_header, send_data, &mailbox);
    return;
}
#endif
