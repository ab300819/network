//
// Created by mason on 2022/4/22.
//

#ifndef UNIX_PROGRAMMING_SRC_ESSENTIAL_CHAPTER2_H_
#define UNIX_PROGRAMMING_SRC_ESSENTIAL_CHAPTER2_H_
#include <iostream>
bool seq_elem(int pos, int& elem);
const int seq_cnt = 6;
const std::vector<int>* (*seq_array[seq_cnt])(int);

#endif	// UNIX_PROGRAMMING_SRC_ESSENTIAL_CHAPTER2_H_
