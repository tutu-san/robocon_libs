#include "roboa_canid.hpp"

//canid_gen 
uint64_t canid_generater_power(read_or_write_enum read_or_write, power_contents_name_enum contents_name, int board_number){
    return static_cast<uint64_t>(read_or_write) + static_cast<uint64_t>(board_select_enum::power_board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number];
}

uint64_t canid_generater_ccc(read_or_write_enum read_or_write, ccc_contents_name_enum contents_name, int board_number, int motor_number){
    return static_cast<uint64_t>(read_or_write) + static_cast<uint64_t>(board_select_enum::ccc_board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number] + motor_number_arr[motor_number];
}

uint64_t canid_generater_gpio(read_or_write_enum read_or_write, gpio_board_contents_name_enum contents_name, int board_number){
    return static_cast<uint64_t>(read_or_write) + static_cast<uint64_t>(board_select_enum::gpio_board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number];
}