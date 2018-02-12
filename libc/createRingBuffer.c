#include <ring_buffer.h>
#include <stdlib.h>
RingBuffer* createRingBuffer(uint8_t capacity) {
	RingBuffer* retval = malloc(sizeof(RingBuffer));
	retval->capacity = capacity;
	retval->filled = 0;
	retval->head = 0;
	retval->tail = 0;
	retval->buffer = malloc(sizeof(uint8_t) * capacity);
	return retval;
}

int8_t destroyRingBuffer(RingBuffer **ringBufferPointerAddress) {
	uint8_t retval = -1;
	RingBuffer *ringBuffer = (*ringBufferPointerAddress);
	if (ringBuffer != NULL) {
		free(ringBuffer->buffer);
		free(ringBuffer);
		*ringBufferPointerAddress = NULL;
		retval = 0;
	}
	return retval;
}