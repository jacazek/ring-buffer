#include <ring_buffer.h>
#include "../Unity/unity.h"
//#include <stdio.h>

RingBuffer* ringBuffer;

void setUp() {
	ringBuffer = createRingBuffer(5);
}

void tearDown() {
}

void GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity() {
	TEST_ASSERT_EQUAL_UINT8(5, ringBuffer->capacity);
}

void GivenACapacity_WhenCreateRingBuffer_RingBufferInitializedCorrectly() {
	TEST_ASSERT_EQUAL_UINT8(0, ringBuffer->head);
	TEST_ASSERT_EQUAL_UINT8(0, ringBuffer->filled);
	TEST_ASSERT_BIT_HIGH(OVERWRITE_EN, ringBuffer->settings);
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity);
	RUN_TEST(GivenACapacity_WhenCreateRingBuffer_RingBufferInitializedCorrectly);
	return UNITY_END();
};
