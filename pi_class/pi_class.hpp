#pragma once
#ifndef PI_CLASS_OLD
#define PI_CLASS_OLD

/**
 * @file pi_class.hpp
 * @brief pi_class header file
 * @details 後方互換性を持たせるために、ここに pid_controllerにつながるヘッダファイルを残す
 */

#include "../pid_controller/pid_controller.hpp"

class pi_class : public pid_controller{
public:
    using pid_controller::pid_controller;
}

#endif