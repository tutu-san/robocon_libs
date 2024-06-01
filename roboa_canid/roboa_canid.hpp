#pragma once
#ifndef ROBOA_CAN_ID
#define ROBOA_CAN_ID

#include <cstdint>
#include <array>

//board_select
#define CCC_BOARD
enum class board_select_enum : uint64_t{
    power_board,
    ccc_board
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
#ifdef POWER_BOARD

enum class contents_type_t : int{
    none,
    state,
    cell,
    ems_request,
    out_v,
    monitor_period,
    monitor_reg
};

constexpr static std::array<uint64_t, 7>contents_name_arr = {
    0x00, //none
    0x01, //state (ems_state)
    0x02, //cell (ripo-cellnumbers)
    0x03, //ems_request (from_pc)
    0x04, //out_v (volt form ripo)
    0xF0, //monitor_period (board -> pc feedback period)
    0xF1  //motor_reg (monitor_data select)
};

//can_data と比較するやつ
enum class ems_state : uint8_t{
    MANUAL_EMS = 0,
    SOFT_EMS = 1
};
#endif

//ccc_board
#ifdef CCC_BOARD

//motor_select
constexpr static std::array<uint64_t, 5>motor_number_arr = {
    0x00000000,
    0x00001000,
    0x00002000,
    0x00003000,
    0x00004000
};
constexpr static uint64_t motor_number = motor_number_arr[0];

//contents select
enum class contents_name_enum : uint64_t{
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
#endif

uint64_t canid_generater(board_select_enum board, contents_name_enum contents_name, int board_number = 1){
    return static_cast<uint64_t>(board) + static_cast<uint64_t>(contents_name) + board_number_arr[board_number];
}

#endif