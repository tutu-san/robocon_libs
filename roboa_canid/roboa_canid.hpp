#pragma once
#ifndef ROBOA_CAN_ID
#define ROBOA_CAN_ID
#endif

#include <cstdint>
#include <array>

#define BOARD_SELECT

//power_board
enum power_board_ids_enum : int{
    none = 0,
    state,
    cell,
    ems_request,
    out_v,
    monitor_period,
    motor_reg
};
enum class ems_state : uint8_t{
    MANUAL_EMS = 0,
    SOFT_EMS = 1
};
constexpr static std::array<uint64_t, 7>contents_name ={
    0x00, //none
    0x01, //state (ems_state)
    0x02, //cell (ripo-cellnumbers)
    0x03, //ems_request (from_pc)
    0x04, //out_v (volt form ripo)
    0xF0, //monitor_period (board -> pc feedback period)
    0xF1  //motor_reg (monitor_data select)
};
constexpr static uint64_t power_board =  0x00000000;
constexpr static std::array<uint64_t, 7> power_board_ids ={
    power_board + contents_name[none],
    power_board + contents_name[state],
    power_board + contents_name[cell],
    power_board + contents_name[ems_request],
    power_board + contents_name[out_v],
    power_board + contents_name[monitor_period],
    power_board + contents_name[motor_reg]
};

//ccc_board
enum motor_select_enum : int{
    motor_0,
    motor_1,
    motor_2,
    motor_3    
};
enum ccc_board_order_enum : int{
    none,
    motor_type,
    control_mode,
    gear_ratio,
    can_timeout,
    pwm_now_data,
    pwm_terget,
    spd_now_data,
    spd_target,
    spd_pwm_limit,
    spd_gain_p,
    spd_gain_i,
    spd_gain_d,
    spd_integral_reset,
    pos_now_data,
    pos_target,
    pos_spd_limit,
    pos_gain_p,
    pos_gain_i,
    pos_gain_d,
    pos_integral_reset,
    monitor_period,
    monitor_reg
};
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
constexpr static uint64_t ccc_board = 0x00000000;
constexpr static uint64_t board_num = 0x00010000; //上から4桁目をいじる
constexpr static std::array<uint64_t, 4>motor_number = {
    0x00000000,
    0x00001000,
    0x00002000,
    0x00003000,
};
constexpr static std::array<uint64_t, 23>contents_name ={
    0x00, //none
    0x01, //motor_type (motor_type)
    0x02, //control_mode (control_mode)
    0x03, //gear_ratio
    0x04, //can_timeout (common/注:どのモーターidで来るかわからないので、共通で設定しておくこと)
    0x10, //pwm_now_data (現在出力中のpwm数値を送る(0.0~1.0/ float))
    0x11, //pwm_terget (pwm指令値(from pc 0.0~1.0/ float))
    0x20, //spd_now_data (現在のrad/s値を送る(float))
    0x21, //spd_target (目標rad/s値を受信(float))
    0x22, //spd_pwm_limit (トルク制限(おそらく電流？))
    0x23, //spd_gain_p (速度pidのPゲイン変更)
    0x24, //spd_gain_i (速度pidのIゲイン変更)
    0x25, //spd_gain_d (速度pidのDゲイン変更)
    0x26, //spd_integral_reset (速度PID制御器, 累積値をリセット / for 停止時など)
    0x30, //pos_now_data (現在の角度値を送信(rad) / PCからの受信の場合は、現在の角度基準設定)
    0x31, //pos_target (位置PIDの目標角度を受信(rad))
    0x32, //pos_spd_limit(速度制限(エンコーダー暴走防止用？))
    0x33, //pos_gain_p (位置pidのPゲイン変更)
    0x34, //pos_gain_i (位置pidのIゲイン変更)
    0x35, //pos_gain_d (位置pidのDゲイン変更)
    0x36, //pos_integral_reset(位置PID制御器, 累積値をリセット)
    0xF0, //monitor_period (board -> pc feedback period)
    0xF1  //monitor_reg (monitor_data select)
};
constexpr static std::array<std::array<uint64_t, 23>, 4> ccc_board_ids ={
    {ccc_board + board_num + motor_number[motor_0] + contents_name[none], ccc_board + board_num + motor_number[motor_0] + contents_name[motor_type], ccc_board + board_num + motor_number[motor_0] + contents_name[control_mode], ccc_board + board_num + motor_number[motor_0] + contents_name[gear_ratio], ccc_board + board_num + motor_number[motor_0] + contents_name[can_timeout], ccc_board + board_num + motor_number[motor_0] + contents_name[pwm_now_data], ccc_board + board_num + motor_number[motor_0] + contents_name[pwm_terget], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_now_data], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_target], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_pwm_limit], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_gain_p], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_gain_i], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_gain_d], ccc_board + board_num + motor_number[motor_0] + contents_name[spd_integral_reset], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_now_data], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_target], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_spd_limit], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_gain_p], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_gain_i], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_gain_d], ccc_board + board_num + motor_number[motor_0] + contents_name[pos_integral_reset], ccc_board + board_num + motor_number[motor_0] + contents_name[monitor_period], ccc_board + board_num + motor_number[motor_0] + contents_name[monitor_reg]},
    {ccc_board + board_num + motor_number[motor_1] + contents_name[none], ccc_board + board_num + motor_number[motor_1] + contents_name[motor_type], ccc_board + board_num + motor_number[motor_1] + contents_name[control_mode], ccc_board + board_num + motor_number[motor_1] + contents_name[gear_ratio], ccc_board + board_num + motor_number[motor_1] + contents_name[can_timeout], ccc_board + board_num + motor_number[motor_1] + contents_name[pwm_now_data], ccc_board + board_num + motor_number[motor_1] + contents_name[pwm_terget], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_now_data], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_target], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_pwm_limit], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_gain_p], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_gain_i], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_gain_d], ccc_board + board_num + motor_number[motor_1] + contents_name[spd_integral_reset], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_now_data], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_target], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_spd_limit], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_gain_p], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_gain_i], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_gain_d], ccc_board + board_num + motor_number[motor_1] + contents_name[pos_integral_reset], ccc_board + board_num + motor_number[motor_1] + contents_name[monitor_period], ccc_board + board_num + motor_number[motor_1] + contents_name[monitor_reg]},
    {ccc_board + board_num + motor_number[motor_2] + contents_name[none], ccc_board + board_num + motor_number[motor_2] + contents_name[motor_type], ccc_board + board_num + motor_number[motor_2] + contents_name[control_mode], ccc_board + board_num + motor_number[motor_2] + contents_name[gear_ratio], ccc_board + board_num + motor_number[motor_2] + contents_name[can_timeout], ccc_board + board_num + motor_number[motor_2] + contents_name[pwm_now_data], ccc_board + board_num + motor_number[motor_2] + contents_name[pwm_terget], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_now_data], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_target], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_pwm_limit], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_gain_p], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_gain_i], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_gain_d], ccc_board + board_num + motor_number[motor_2] + contents_name[spd_integral_reset], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_now_data], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_target], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_spd_limit], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_gain_p], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_gain_i], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_gain_d], ccc_board + board_num + motor_number[motor_2] + contents_name[pos_integral_reset], ccc_board + board_num + motor_number[motor_2] + contents_name[monitor_period], ccc_board + board_num + motor_number[motor_2] + contents_name[monitor_reg]},
    {ccc_board + board_num + motor_number[motor_3] + contents_name[none], ccc_board + board_num + motor_number[motor_3] + contents_name[motor_type], ccc_board + board_num + motor_number[motor_3] + contents_name[control_mode], ccc_board + board_num + motor_number[motor_3] + contents_name[gear_ratio], ccc_board + board_num + motor_number[motor_3] + contents_name[can_timeout], ccc_board + board_num + motor_number[motor_3] + contents_name[pwm_now_data], ccc_board + board_num + motor_number[motor_3] + contents_name[pwm_terget], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_now_data], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_target], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_pwm_limit], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_gain_p], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_gain_i], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_gain_d], ccc_board + board_num + motor_number[motor_3] + contents_name[spd_integral_reset], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_now_data], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_target], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_spd_limit], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_gain_p], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_gain_i], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_gain_d], ccc_board + board_num + motor_number[motor_3] + contents_name[pos_integral_reset], ccc_board + board_num + motor_number[motor_3] + contents_name[monitor_period], ccc_board + board_num + motor_number[motor_3] + contents_name[monitor_reg]},
};