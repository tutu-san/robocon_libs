/*
 * switch_filter.cpp
 *
 *  Created on: Sep 15, 2023
 *      Author: tutusan
 */

#include "switch_filter.hpp"

//初期設定
// true 0xff, false:0
switch_filter::switch_filter(bool _value):now(_value),last(_value) {
	// TODO Auto-generated constructor stub
    history = _value ? 0xFF : 0;
}

switch_filter::~switch_filter() {
	// TODO Auto-generated destructor stub
}

//true:1 false:0
// 一番左に t/fを入れるイメージ
//trueが続くと trueを返すようになる 逆もしかり(のはず)
void switch_filter::update(bool next){
	history = history <<1 | next;
	last = now;
	if (history== 0){
	  now = false;
	}else if(history == 0xFF){
	  now = true;
	}
}

//結果を返す
// read() nowの状態を t/fで返す
bool switch_filter::read()const{
   return now;
}

//is_rased last: false かつ now: true の場合のみ trueを返す
bool switch_filter::is_raised()const{
	return now && !last;
}

//is_fall last: true かつ now: falseの場合のみ trueを返す
bool switch_filter::is_fall()const{
	return !now && last;
}

//is_changed lastとnowが異なる場合 trueを返す
bool switch_filter::is_changed()const{
	return now ^ last;
}
