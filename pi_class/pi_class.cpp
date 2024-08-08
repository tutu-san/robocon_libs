#include "pi_class.hpp"
//実際にPI制御を計算するメソッド
float pi_class::pi_calc(float current_value){
    //計算
    const float error = terget_value - current_value; //エラー値(目標との差)
    integral += error * delta_t; //積分を差分の累積で代用
    // const float derivative = (error - prev_error) / delta_t; //微分
    // prev_error = error; //エラー値保存)(微分)

    clamp(integral, -10000.0f, 10000.0f); //累積値上限設定 必要に応じて変更

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
void pi_class::update_terget(float new_terget_value){
    terget_value = new_terget_value;
    return;
}

//累積値(積分値)をリセットするメソッド
void pi_class::reset_integral(){
    integral = 0.0f;
    return;
}

//PI制御器のON/OFFを切り替えるメソッド
void pi_class::pi_enabled(bool usr_input){
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
float pi_class::run_pi_controller(float current_value){
    float result = 0.0f;
    if(pi_on == true){
        result = pi_calc(current_value);
    }else{
        result = terget_value; //目標値をそのまま返すようになる
    }
    _debug_result = result;
    return result;
}

//通信でゲインを変更することを想定しているメソッド
void pi_class::update_p_gain(float new_p_gain){
    gain_p = new_p_gain;
    return;
}

void pi_class::update_i_gain(float new_i_gain){
    gain_i = new_i_gain;
    return;
}


//taichi_input
float pi_class::taichi_input_target(float target_deg, float now_pos){
    const int minius = target_deg > 0 ? 1 : -1;
    const int counter_36 = abs(target_deg) / 10;
    const float amari = ((abs((int)target_deg) % 10) / 10.0f) * 8191.0f;
    const float result = ((angle_to_rad * (amari + counter_36 * resolution * minius)) / 36.0f) + now_pos;

    terget_value = result * 36;

    return 0.0f;
}
