#ifndef _TEST_H_
#define _TEST_H_
#include "../Unity/unity.h"

// TODO: handle more than 64 bit architecture
#define TEST_ASSERT_POINTER_EQUAL(value, pointer) TEST_ASSERT_EQUAL_UINT64(value, pointer);
#define TEST_ASSERT_POINTER_NOT_EQUAL(value, pointer) TEST_ASSERT_NOT_EQUAL(value, pointer);

#endif