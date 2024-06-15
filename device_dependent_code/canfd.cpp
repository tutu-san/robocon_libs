#include "canfd.hpp"

#ifdef ENABLE_CANFD
void can_send(void* canfd_handle, uint32_t can_id, uint8_t(&send_data)[8], bool extended_id){
    FDCAN_HandleTypeDef* canfd_handle = (FDCAN_HandleTypeDef*)_canfd_handle;
    CAN_TxHeaderTypeDef tx_header;
    uint8_t mailbox;
    
    //header settings
    tx_header.Identifier = can_id;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;
    tx_header.DataLength = FDCAN_DLC_BYTES_8;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker = 0;
    if(extended_id){
        tx_header.IdType = FDCAN_EXTENDED_ID;
    }else{
        tx_header.IdType = FDCAN_STANDARD_ID;
    }

	HAL_FDCAN_AddMessageToTxFifoQ(canfd_handle, &tx_header, send_data);
}
#endif
