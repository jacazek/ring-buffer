#include <ring_buffer.h>
#include "../Unity/unity.h"
#include <test.h>
//#include <stdio.h>

RingBuffer* ringBuffer = NULL;

void setUp() {
	ringBuffer = createRingBuffer(5);
}

void tearDown() {
	if (ringBuffer != NULL) {
		destroyRingBuffer(&ringBuffer);
	}
}

void GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity() {
	TEST_ASSERT_EQUAL_UINT8(5, ringBuffer->capacity);
	TEST_ASSERT_NOT_NULL(ringBuffer);
}

void GivenACapacity_WhenCreateRingBuffer_RingBufferInitializedCorrectly() {
	TEST_ASSERT_EQUAL_UINT8(0, ringBuffer->head);
	TEST_ASSERT_EQUAL_UINT8(0, ringBuffer->tail);
	TEST_ASSERT_EQUAL_UINT8(0, ringBuffer->filled);
}

void GivenARingBuffer_WhenDestroyed_RingBufferIsDestroyed() {
	TEST_ASSERT_EQUAL_UINT8(0, destroyRingBuffer(&ringBuffer));
	TEST_ASSERT_NULL(ringBuffer);
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(GivenACapacity_WhenCreateRingBuffer_RingBufferHasRequestedCapacity);
	RUN_TEST(GivenACapacity_WhenCreateRingBuffer_RingBufferInitializedCorrectly);
	RUN_TEST(GivenARingBuffer_WhenDestroyed_RingBufferIsDestroyed);
	return UNITY_END();
};
