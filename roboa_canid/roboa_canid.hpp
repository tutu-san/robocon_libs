#pragma once
#ifndef ROBOA_CAN_ID
#define ROBOA_CAN_ID

#include <cstdint>
#include <array>

//read or write(基板側から見て)
enum class read_or_write_enum : uint64_t{
    read = 0x00000000,
    write = 0x10000000
};

//board_select
enum class board_select_enum : uint64_t{
    power_board = 0x01000000,
    ccc_board = 0x02000000
};

//(common) board_number
constexpr static std::array<uint64_t, 5> board_number_arr = {
    0x00000000,
    0x00010000,
    0x00020000,
    0x00030000,
    0x00040000
};
constexpr static uint64_t board_number = board_number_arr[0];

//power_board
//contents_select
enum class power_contents_name_enum : uint64_t{
    none = 0x00,
    state = 0x01,
    cell = 0x02,
    ems_request = 0x03,
    out_v = 0x04,
    monitor_period = 0xF0,
    monitor_reg = 0xF1
};

//can_data と比較するやつ
enum class ems_state : uint8_t{
    MANUAL_EMS = 0,
    SOFT_EMS = 1
};

//ccc_board
//motor_select
constexpr static std::array<uint64_t, 5>motor_number_arr = {
    0x00000000,
    0x00000100,
    0x00000200,
    0x00000300,
    0x00000400
};

//contents select
enum class ccc_contents_name_enum : uint64_t{
    none = 0x00,
    motor_type = 0x01,
    control_mode = 0x02,
    gear_ratio = 0x03,
    can_timeout = 0x04,
    pwm_now_data = 0x10,
    pwm_terget = 0x11,
    spd_now_data = 0x20,
    spd_target = 0x21,
    spd_pwm_limit = 0x22,
    spd_gain_p = 0x23,
    spd_gain_i = 0x24,
    spd_gain_d = 0x25,
    spd_integral_reset = 0x26,
    pos_now_data = 0x30,
    pos_target = 0x31,
    pos_spd_limit = 0x32,
    pos_gain_p = 0x33,
    pos_gain_i = 0x34,
    pos_gain_d = 0x35,
    pos_integral_reset = 0x36,
    monitor_period = 0xF0,
    monitor_reg = 0xF1
};

//can_data と比較するやつ
enum class motor_type : uint8_t {
    C610_C620,
    DCMD,
    VESC
};
enum class control_mode : uint8_t {
    PWM_MODE,
    SPD,
    POS
};

//canid_gen 
uint64_t canid_generater(read_or_write_enum read_or_write, board_select_enum board, power_contents_name_enum contents_name, int board_number = 1);

uint64_t canid_generater(read_or_write_enum read_or_write, board_select_enum board, ccc_contents_name_enum contents_name, int board_number = 1, int motor_number = 0);

#endif