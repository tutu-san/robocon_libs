#include <iostream>
#include <cstdint>
#include <array>

using namespace std;

//board select
#define POWER_BOARD

#ifdef POWER_BOARD
constexpr static uint64_t board_id = 0x10000000;

enum class contents_type_t : int {
    none,
    reset,
    eat
};

constexpr static array<uint8_t, 3> contents_name_arr = {
    0x00, //none
    0x01, //reset
    0x02  //eat
};
#endif

constexpr static array<uint64_t, 4> board_number_arr = {
    0x00010000,
    0x00020000,
    0x00030000,
    0x00040000
};

//board number select (maltipul board)
constexpr static uint64_t board_number = board_number_arr[0];

uint64_t can_id_gen(contents_type_t contents_name){
    return board_id + board_number + contents_name_arr[static_cast<int>(contents_name)];
}

int main(){
    using enum contents_type_t;
    uint64_t id = can_id_gen(none);
    cout << "id: " << showbase << hex << id << endl;
    return 0;
}


