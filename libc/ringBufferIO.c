#include <ring_buffer.h>

void advanceHead(RingBuffer *ringBuffer) {
	ringBuffer->head++;
	if (ringBuffer->head == ringBuffer->capacity) {
		ringBuffer->head = 0;
	}
}

void writeRingBuffer(RingBuffer *ringBuffer, char value) {
	ringBuffer->buffer[ringBuffer->head] = value;
	advanceHead(ringBuffer);
	if (ringBuffer->filled < ringBuffer->capacity) {
		ringBuffer->filled += 1;
	}
}

int8_t readRingBuffer(RingBuffer *ringBuffer, char *value) {
	int8_t retval = -1;
	if (ringBuffer->filled > 0) {
		int8_t tail = ringBuffer->head - ringBuffer->filled;
		(*value) = ringBuffer->buffer[tail < 0 ? tail + ringBuffer->capacity : tail];
		ringBuffer->filled -= 1;
		retval = 0;
	}
	return retval;
}