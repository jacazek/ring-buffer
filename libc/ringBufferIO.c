#include <ring_buffer.h>

int8_t isFull(RingBuffer *ringBuffer) {
	return ringBuffer->head == ringBuffer->tail && ringBuffer->filled > 0 ? 1 : 0;
}

int8_t isEmpty(RingBuffer *ringBuffer) {
	return ringBuffer->head == ringBuffer->tail && ringBuffer->filled == 0 ? 1 : 0;
}

void adjustFill(RingBuffer *ringBuffer, int8_t amount) {
	ringBuffer->filled += amount;
}

void advanceHead(RingBuffer *ringBuffer) {
	ringBuffer->head++;
	if (ringBuffer->head == ringBuffer->capacity) {
		ringBuffer->head = 0;
	}
}

void advanceTail(RingBuffer *ringBuffer) {
	ringBuffer->tail++;
	if (ringBuffer->tail == ringBuffer->capacity) {
		ringBuffer->tail = 0;
	}
}

int8_t writeRingBuffer(RingBuffer *ringBuffer, uint8_t value) {
	uint8_t retval = -1;
	if (!isFull(ringBuffer)) {
		ringBuffer->buffer[ringBuffer->head] = value;
		adjustFill(ringBuffer, 1);
		advanceHead(ringBuffer);
		retval = 0;
	}
	return retval;
}

int8_t readRingBuffer(RingBuffer *ringBuffer, uint8_t *value) {
	int8_t retval = -1;
	if (!isEmpty(ringBuffer)) {
		(*value) = ringBuffer->buffer[ringBuffer->tail];
		adjustFill(ringBuffer, -1);
		advanceTail(ringBuffer);
		retval = 0;
	}
	return retval;
}