#include <ring_buffer.h>
#include "../Unity/unity.h"
#include "./createRingBuffer.c"

RingBuffer ringBufferActual;
RingBuffer *ringBuffer;
char buffer[2];

void setUp() {
	ringBufferActual = createRingBuffer(2, buffer);
	ringBuffer = &ringBufferActual;
}

void tearDown() {
}

void GivenARingBuffer_WhenWrite_ThenByteWriteSuccessful() {
	writeRingBuffer(ringBuffer, 5);
	TEST_ASSERT_EQUAL_UINT8(1, ringBuffer->filled);
}

void GivenAFullRingBufferWithOverwriteEnabled_WhenWrite_ThenByteWriteOverwrites() {
	writeRingBuffer(ringBuffer, 5);
	writeRingBuffer(ringBuffer, 7);
	TEST_ASSERT_EQUAL_INT8(0, writeRingBuffer(ringBuffer, 5));
	TEST_ASSERT_EQUAL_UINT8(2, ringBuffer->filled);
}

void GivenAFullRingBufferWithOverwriteDisabled_WhenWrite_ThenByteWriteFails() {
	ringBuffer->settings &= ~(1<<OVERWRITE_EN);
	writeRingBuffer(ringBuffer, 5);
	writeRingBuffer(ringBuffer, 7);
	TEST_ASSERT_EQUAL_INT8(-1, writeRingBuffer(ringBuffer, 5));
	TEST_ASSERT_EQUAL_UINT8(2, ringBuffer->filled);
}

void GivenARingBufferWithValueX_WhenRead_ThenValueReturned() {
	uint8_t value = 0;
	writeRingBuffer(ringBuffer, 5);
	TEST_ASSERT_EQUAL_INT8(0, readRingBuffer(ringBuffer, &value));
	TEST_ASSERT_EQUAL_UINT8(5, value);
}

void GivenARingBufferWithXValues_WhenReadXTimes_ThenValuesRead() {
	uint8_t value = 0;
	writeRingBuffer(ringBuffer, 5);
	writeRingBuffer(ringBuffer, 10);
	readRingBuffer(ringBuffer, &value);
	TEST_ASSERT_EQUAL_UINT8(5, value);
	readRingBuffer(ringBuffer, &value);
	TEST_ASSERT_EQUAL_UINT8(10, value);
}

void GivenARingBufferWithXValues_WhenRead1Time_ThenFilledDecremented() {
	uint8_t value = 0;
	writeRingBuffer(ringBuffer, 5);
	writeRingBuffer(ringBuffer, 10);
	TEST_ASSERT_EQUAL_UINT8(2, ringBuffer->filled);
	readRingBuffer(ringBuffer, &value);
	TEST_ASSERT_EQUAL_UINT8(1, ringBuffer->filled);
}

void GivenAnEmptyBuffer_WhenRead_ThenReadFails() {
	uint8_t value = 0;
	TEST_ASSERT_EQUAL_INT8(-1, readRingBuffer(ringBuffer, &value));
}

void GivenEnEmptyBuffer_WhenWriteThenRead_ThenBufferCycles() {
	ringBufferActual = createRingBuffer(8, buffer);
	uint8_t i=0;
	char out = 0;
	for (i = 0; i < 16; i ++) {
		writeRingBuffer(&ringBufferActual, i);
		TEST_ASSERT_EQUAL_UINT8(1, ringBufferActual.filled);
		readRingBuffer(&ringBufferActual, &out);
		TEST_ASSERT_EQUAL_UINT8(i, out);
		TEST_ASSERT_EQUAL_UINT8(0, ringBufferActual.filled);
	}
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(GivenARingBuffer_WhenWrite_ThenByteWriteSuccessful);
	RUN_TEST(GivenAFullRingBufferWithOverwriteEnabled_WhenWrite_ThenByteWriteOverwrites);
	RUN_TEST(GivenAFullRingBufferWithOverwriteDisabled_WhenWrite_ThenByteWriteFails);
	RUN_TEST(GivenARingBufferWithValueX_WhenRead_ThenValueReturned);
	RUN_TEST(GivenARingBufferWithXValues_WhenReadXTimes_ThenValuesRead);
	RUN_TEST(GivenARingBufferWithXValues_WhenRead1Time_ThenFilledDecremented);
	RUN_TEST(GivenAnEmptyBuffer_WhenRead_ThenReadFails);
	return UNITY_END();
};
