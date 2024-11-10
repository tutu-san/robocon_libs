#include "pid_controller.hpp"
//実際にPI制御を計算するメソッド
float pid_controller::pi_calc(float current_value){
    //計算
    const float error = target_value - current_value; //エラー値(目標との差)
    integral += error * delta_t; //積分を差分の累積で代用
    // const float derivative = (error - prev_error) / delta_t; //微分
    // prev_error = error; //エラー値保存)(微分)

    clamp(integral, -integral_max, integral_max); //累積値上限設定 必要に応じて変更

    //gainをかける
    float result_p = 0.0f, result_i = 0.0f;
    // float result_d = 0.0f;
    result_p = error * gain_p;
    result_i = integral * gain_i;
    // result_d = derivative * gain_d;


    //計算結果を返す
    float pi_result = 0.0f;
    pi_result = result_p + result_i;
    // pi_result += result_d;
    //pi制御の結果そのものにクランプをかけるのは、結果を受け取ったメソッドで行うべき
    return pi_result;
}

//目標値を変更するメソッド
void pid_controller::update_target(float new_target_value){
    if(new_target_value > target_upper_limit){
        target_value = target_upper_limit;
    }else if(new_target_value < target_lower_limit){
        target_value = target_lower_limit;
    }else{
        target_value = new_target_value;
    }
    return;
}

//目標値の変更に制限をかけるメソッド(>0なら上限 <0なら下限とするが、オプションで絶対値とすることができる)
//update_target()が、自動設定される場合に制限をかけられるようにする
void pid_controller::set_target_limit(float new_target_limit, bool is_abs_target_limit){
	if(is_abs_target_limit){
        target_lower_limit = -fabs(new_target_limit);
        target_upper_limit = fabs(new_target_limit);
    }else{
        if(new_target_limit > 0){
            target_upper_limit = new_target_limit;
        }else if(new_target_limit < 0){
            target_lower_limit = new_target_limit;
        }else{
            set_target_limit(0, true);
        }
    }
}

//累積値(積分値)をリセットするメソッド
void pid_controller::reset_integral(){
    integral = 0.0f;
    return;
}

//PI制御器のON/OFFを切り替えるメソッド
void pid_controller::pi_enabled(bool usr_input){
    if(usr_input == true){
        pi_on = true;
        return;
    }else if(usr_input == false){
        pi_on = false; //実行時, terget_valueをそのまま返すようになる
        return;
    }else{
        return; //不正
    }
    return;
}

//PI制御器の状態をチェックして実行するメソッド
float pid_controller::run_pi_controller(float current_value){
    float result = 0.0f;
    if(pi_on == true){
        result = pi_calc(current_value);
    }else{
        result = target_value; //目標値をそのまま返すようになる
    }
    _debug_result = result;
    return result;
}

//通信でゲインを変更することを想定しているメソッド
void pid_controller::update_p_gain(float new_p_gain){
    gain_p = new_p_gain;
    return;
}

void pid_controller::update_i_gain(float new_i_gain){
    gain_i = new_i_gain;
    return;
}

float pid_controller::show_now_target(){
    return target_value;
}
