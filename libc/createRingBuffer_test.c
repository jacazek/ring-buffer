#include <ring_buffer.h>
#include "../Unity/unity.h"
#include <test.h>
//#include <stdio.h>

RingBuffer* ringBuffer = 0;

void setUp() {
	ringBuffer = createRingBuffer(5);
}

void tearDown() {
	if (ringBuffer != 0) {
		destroyRingBuffer(ringBuffer);
	}
}

void GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity() {
	TEST_ASSERT_EQUAL_UINT8(5, ringBuffer->capacity);
	TEST_ASSERT_POINTER_NOT_EQUAL(0, ringBuffer);
}

void GivenARingBuffer_WhenDestroyed_RingBufferIsDestroyed() {
	TEST_ASSERT_EQUAL_UINT8(0, destroyRingBuffer(ringBuffer));
	TEST_ASSERT_POINTER_EQUAL(0, ringBuffer);
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity);
	return UNITY_END();
};
