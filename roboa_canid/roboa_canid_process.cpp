#include "roboa_canid_process.hpp"

std::unordered_map<uint32_t, std::function<void(const uint8_t(&)[8])>> can_receive_handlers;

using enum read_or_write_enum;

void init_can_receive_handlers(){
    //power
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::none)] = [](const uint8_t(&)[8]){
        //none
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::state)] = [](const uint8_t(&)[8]){
        //none
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::cell)] = [](const uint8_t(&)[8]){
        //none
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::ems_request)] = [](const uint8_t(&)[8]){
        //todo:when ems pushed?
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::out_v)] = [](const uint8_t(&)[8]){
        //none
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::monitor_period)] = [](const uint8_t(&)[8]){
        //none
    };
    can_receive_handlers[canid_generater_power(read, power_contents_name_enum::monitor_reg)] = [](const uint8_t(&)[8]){
        //none
    };

    //ccc motor
    for(int i=0; i<4; i++){
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::none, i)] = [](const uint8_t(&)[8]){
            //none
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::motor_type, i)] = [](const uint8_t(&)[8]){
            //todo: encoder motor_change?
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::control_mode, i)] = [](const uint8_t(&)[8]){
            //todo: pi class settings chenge
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::gear_ratio, i)] = [](const uint8_t(&)[8]){
            //todo: encoder? (非モーター部(機構)によるギア比)
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::can_timeout, i)] = [](const uint8_t(&)[8]){
            //todo: timer_counter set
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pwm_now_data, i)] = [](const uint8_t(&)[8]){
            //none(書き込み専用)
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pwm_terget, i)] = [](const uint8_t(&)[8]){
            //todo: pi class input data(pwm mode) or input pwmdata robomas_rotate directly
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_now_data, i)] = [](const uint8_t(&)[8]){
            //none(書き込み専用)
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_target, i)] = [](const uint8_t(&)[8]){
            //todo: set terget spd
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_pwm_limit, i)] = [](const uint8_t(&)[8]){
            //電流制限か、pwm値制限か
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_gain_p, i)] = [](const uint8_t(&)[8]){
            //todo: spd pi class input p gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_gain_i, i)] = [](const uint8_t(&)[8]){
            //todo: spd pi class input i gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_gain_d, i)] = [](const uint8_t(&)[8]){
            //todo: spd pi class input d gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::spd_integral_reset, i)] = [](const uint8_t(&)[8]){
            //todo: spd pi class reset integral
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_now_data, i)] = [](const uint8_t(&)[8]){
            //none(書き込み専用)
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_target, i)] = [](const uint8_t(&)[8]){
            //todo: set terget pos 
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_spd_limit, i)] = [](const uint8_t(&)[8]){
            //速度制限?
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_gain_p, i)] = [](const uint8_t(&)[8]){
            //todo: pos pi class input p gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_gain_i, i)] = [](const uint8_t(&)[8]){
            //todo: pos pi class input i gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_gain_d, i)] = [](const uint8_t(&)[8]){
            //todo: pos pi class input d gain
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::pos_integral_reset, i)] = [](const uint8_t(&)[8]){
            //todo: pos pi class reset internal
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::monitor_period, i)] = [](const uint8_t(&)[8]){
            //timer_counter set
        };
        can_receive_handlers[canid_generater_ccc(read, ccc_contents_name_enum::monitor_reg, i)] = [](const uint8_t(&)[8]){
            //send data serect?
        };
    }
}

int handle_can_receive_message(uint32_t can_id, uint8_t(&can_data)[8]){
    auto it = can_receive_handlers.find(can_id);
    if(it != can_receive_handlers.end()){
        it->second(can_data); //idに応じた処理
        return 0;
    }else if{
        return 1; //登録されていないid LEDの点灯などで知らせる
    }
}