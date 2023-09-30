#ifndef COMMON_HPP
#define COMMON_HPP
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <assert.h>
#include "reverse_iterator.hpp"

#ifdef _WIN64
	typedef unsigned __int64 size_t;
	typedef __int64          ptrdiff_t;
	typedef __int64          intptr_t;
#else
	typedef unsigned int     size_t;
	typedef int              ptrdiff_t;
	typedef int              intptr_t;
#endif

using syu_reverse::Reverse_Iterator;
using namespace std;

void output_log(const char* title, const char* content);

#endif // COMMON_HPP