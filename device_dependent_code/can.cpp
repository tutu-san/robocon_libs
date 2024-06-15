#include "can.hpp"

void can_send(CAN_Handle_Typedef* can_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id = false){
    CAN_TxHeaderTypeDef tx_header;
    uint8_t mailbox;
    
    //header settings
    tx_header.StdId = can_id;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = 8;
    tx_header.TransmitGlobalTime = DISABLE;
    if(extended_id){
        tx_header.IDE = CAN_ID_EXT;
    }else{
        tx_header.IDE = CAN_ID_STD;
    }

    HAL_CAN_AddTxMessage(can_handle, &tx_header, send_data, mailbox);
    return;
}