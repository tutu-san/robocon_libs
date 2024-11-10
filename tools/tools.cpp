#include "tools.hpp"
#include "../robomas_encoder/robomas_encoder.hpp"
//単位変換系
// rad/s -> rpm
float rad_per_sec_to_rpm(float rad_par_sec){
    constexpr static float rad_per_sec_to_rpm_constant = 60.0f / (2.0f * M_PI);
    return rad_par_sec * rad_per_sec_to_rpm_constant;
}
//rad -> degree
float rad_to_degree(float rad){
    constexpr static float rad_to_degree_constant = 180.0f / M_PI;
    return rad * rad_to_degree_constant;
}
float deg_to_rad(float deg){
	constexpr static float deg_to_rad_constant = M_PI / 180.0f;
	return deg * deg_to_rad_constant;
}
//degree -> robomas_encoder_angle(a.k.a taichi_encoder_input)
float degree_to_robomas_encoder_angle(float target_deg, float now_pos, float gear_ratio){
    //taichi encoder
    const size_t resolution_bit = 13;
    const int resolution = 1<<resolution_bit;
    const float angle_to_rad = 2*M_PI/(float)resolution;

    const int minius = target_deg > 0 ? 1 : -1;
    const int counter_36 = abs(target_deg) / 10;
    const float amari = ((abs((int)target_deg) % 10) / 10.0f) * 8191.0f;
    const float result = ((angle_to_rad * (amari + counter_36 * resolution * minius)) / 36.0f);

    return (result * gear_ratio); //現在角度との差を出し、あとどのくらい修正が必要か見る
}

//型変更系
//uint8_t -> float
float uint8_to_float(uint8_t(&uint_datas)[8]){
    //uint8_t[4] to float
	std::array<uint8_t, 4>tmp2;
	float result;
	for(int i=0; i<4; i++){
		tmp2[i] = uint_datas[i];
	}
	result = std::bit_cast<float>(tmp2); //C++20 required
    //異常値入力の対策については過去ファイルを参照
	return result;
}
//uint8_t -> uint16_t
int uint8_to_int(uint8_t input_data_high, uint8_t input_data_low){
    //上位,下位ビットの統合
    uint16_t unsigned_int_data = input_data_high << 8 | input_data_low;

    int16_t signed_int_data = 0;

    signed_int_data = unsigned_int_data;

    //おしまい
    return signed_int_data;
}
//uint8_t -> uint64_t
uint64_t uint8_to_uint64(uint8_t(&input_data)[8]){
    //上位,中位,下位,下位ビットの統合
    uint64_t unsigned_int_data = static_cast<uint64_t>(input_data[0]) << 56 |
    								static_cast<uint64_t>(input_data[1]) << 48 |
									static_cast<uint64_t>(input_data[2]) << 40 |
									static_cast<uint64_t>(input_data[3]) << 32 |
									static_cast<uint64_t>(input_data[4]) << 24 |
									static_cast<uint64_t>(input_data[5]) << 16 |
									static_cast<uint64_t>(input_data[6]) << 8 |
									static_cast<uint64_t>(input_data[7]);
    //おしまい
    return unsigned_int_data;
}
//float -> uint8_t
void float_to_uint8(float input_float_data, uint8_t(&output_uint8_datas)[8]){
    const uint32_t tmp_32bits_data =std::bit_cast<uint32_t>(input_float_data);
    for(int i = 0; i < 4; i++){
        output_uint8_datas[i] = static_cast<uint8_t>(tmp_32bits_data >> (i * 8));
    }
    return;
}
//uint16_t -> uint8_t
void uint16_to_uint8(uint16_t input, uint8_t(&output_uint8_datas)[8]){
    output_uint8_datas[0] = input >> 8;
    output_uint8_datas[1] = input & 0x00FF;
    return;
}
