
#ifndef TEST_H
#define TEST_H
#pragma once


#include "vector.hpp"
#include "string.hpp"
#include "list.hpp"
//#include "reverse_iterator.hpp" 

void test_string()
{
	Test_string::callTestFunction();

}

void test_vector()
{
	Test_Vector::callTestFunction();
}


void test_list()
{
	Test_list::callTestFunction();
}

#endif // TEST_H