#include <ring_buffer.h>

void advanceHead(RingBuffer *ringBuffer) {
	ringBuffer->head++;
	if (ringBuffer->head == ringBuffer->capacity) {
		ringBuffer->head = 0;
	}
}

uint8_t overwriteEnabled(RingBuffer *ringBuffer) {
	return ringBuffer->settings & (1<<OVERWRITE_EN);
}

int8_t writeRingBuffer(RingBuffer *ringBuffer, char value) {
	int8_t retval = -1;
	uint8_t belowCapacity = ringBuffer->filled < ringBuffer->capacity;
	if (belowCapacity || overwriteEnabled(ringBuffer)) {
		ringBuffer->buffer[ringBuffer->head] = value;
		advanceHead(ringBuffer);
		if (belowCapacity) {
			ringBuffer->filled += 1;
		}
		retval = 0;
	}
	return retval;
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