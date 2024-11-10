#pragma once
#ifndef CANFD_HPP
#define CANFD_HPP

#include "main.h" //cube mx 生成コードを使用しているならこれで行けるはず
#include <cstdint>
#include <string>
#include <span>

#define ENABLE_CANFD 0

#if ENABLE_CANFD
void can_send(void* _canfd_handle, uint32_t can_id, std::span<uint8_t> can_data, bool extended_id = false);

//受信割り込みに関するコードをここに書くかどうか
#endif

#endif
