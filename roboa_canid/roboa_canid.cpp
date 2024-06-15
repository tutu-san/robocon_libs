#include "robomas_encoder.h"

//canid_gen 
uint64_t canid_generater(read_or_write_enum read_or_write, board_select_enum board, power_contents_name_enum contents_name, int board_number){
    return static_cast<uint64_t>(read_or_write) + static_cast<uint64_t>(board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number];
}

uint64_t canid_generater(read_or_write_enum read_or_write, board_select_enum board, ccc_contents_name_enum contents_name, int board_number, int motor_number){
    return static_cast<uint64_t>(read_or_write) + static_cast<uint64_t>(board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number] + motor_number_arr[motor_number];
}