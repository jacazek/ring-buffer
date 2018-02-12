#include <ring_buffer.h>
#include <stdlib.h>
RingBuffer* createRingBuffer(uint8_t capacity) {
	RingBuffer* retval = malloc(sizeof(RingBuffer));
	retval->capacity = capacity;
	return retval;
}

uint8_t destroyRingBuffer(RingBuffer *ringBuffer) {
	uint8_t retval = -1;
	if (ringBuffer != 0) {
		free(ringBuffer->buffer);
		free(ringBuffer);
		ringBuffer = 0;
		retval = 0;
	}
	return retval;
}