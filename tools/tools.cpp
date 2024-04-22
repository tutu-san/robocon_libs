#include "tools.hpp"
//単位変換系
// rad/s -> rpm
float rad_per_sec_to_rpm(float rad_par_sec){
    constexpr static float rad_per_sec_to_rpm_constant = 60.0f / (2.0f * M_PI);
    return rad_par_sec * rad_per_sec_to_rpm_constant;
}
//型変更系
//uint8_t -> float
float uint8_to_float(uint8_t(&uint_datas)[8]){
    //uint8_t[4] to float
	static float save = 0;
	uint8_t tmp2[4];
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
