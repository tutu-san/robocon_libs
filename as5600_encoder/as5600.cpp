#include "as5600.hpp"
void as5600_tool::request_encoder_data(){
    HAL_I2C_Master_Transmit(i2c_handle, as5600_i2c_id, as5600_angle_reg, 1, 50);
    HAL_I2C_Master_Receive_IT(i2c_handle, as5600_i2c_id, rev_buffer_i2c, 2);
}

void as5600_tool::receive_encoder_data(){

}