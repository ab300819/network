//
// Created by mason on 2022/3/26.
//

#pragma once
#ifndef UNIX_PROGRAMMING_LIBS_HELPERS_H_
#define UNIX_PROGRAMMING_LIBS_HELPERS_H_

#include "structs.h"

int calcFibonacci(int);
int __calcFibTCO(int, int, int);
int __calcFibRecursion(int);
int calcDigits(int);
int retrieveGETQueryIntValByKey(char*, const char*);
void wrapStrFromPTR(char*, size_t, const char*, const char*);
void setupServerSettings(int, const char**, serverSettings*);

#endif	// UNIX_PROGRAMMING_LIBS_HELPERS_H_
