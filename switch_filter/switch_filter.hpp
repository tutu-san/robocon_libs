/*
 * switch_filter.hpp
 *
 *  Created on: Sep 15, 2023
 *      Author: tutusan
 */
#pragma once
#ifndef SWITCH_FILTER_HPP_
#define SWITCH_FILTER_HPP_

#include <cstdint>

class switch_filter {
private:
	bool now, last;
	uint8_t history;
public:
	switch_filter(bool);
	switch_filter(const switch_filter&) = default;
	virtual ~switch_filter();
	void update(bool);
	bool read()const;
	bool is_raised()const;
	bool is_fall()const;
	bool is_changed()const;
};

#endif /* SWITCH_FILTER_HPP_ */
