#include "canfd.hpp"

#if ENABLE_CANFD
void can_send(void* _canfd_handle, uint32_t can_id, std::span<uint8_t> can_data, bool extended_id){
    FDCAN_HandleTypeDef* canfd_handle = (FDCAN_HandleTypeDef*)_canfd_handle;
    FDCAN_TxHeaderTypeDef tx_header;
    
    //header settings
    tx_header.Identifier = can_id;
    tx_header.TxFrameType = FDCAN_DATA_FRAME;
    tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
    tx_header.BitRateSwitch = FDCAN_BRS_OFF;
    tx_header.FDFormat = FDCAN_CLASSIC_CAN;
    tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    tx_header.MessageMarker = 0;

    constexpr static uint32_t fdcan_dlcsize_format = 0x00010000;
    tx_header.DataLength = can_data.size() * fdcan_dlcsize_format;

    if(extended_id){
        tx_header.IdType = FDCAN_EXTENDED_ID;
    }else{
        tx_header.IdType = FDCAN_STANDARD_ID;
    }

	HAL_FDCAN_AddMessageToTxFifoQ(canfd_handle, &tx_header, can_data);
}
#endif
