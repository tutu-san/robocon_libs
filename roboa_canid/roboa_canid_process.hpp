#pragma once
#ifndef ROBOA_CAN_REV
#define ROBOA_CAN_REV

#include <unordered_map>
#include <functional>
#include <cstdint>

#include "roboa_canid.hpp"

extern std::unordered_map<uint32_t, std::function<void(const uint8_t(&)[8])>> can_receive_handlers;
void init_can_receive_handlers();
int handle_can_receive_message(uint32_t can_id, uint8_t(&can_data)[8]);

#endif