#include <ring_buffer.h>
#include <stdlib.h>

RingBuffer* createRingBuffer(uint8_t capacity) {
	RingBuffer *retval = malloc(sizeof(RingBuffer));
	retval->settings = (1<<OVERWRITE_EN);
	retval->capacity = capacity;
	retval->filled = 0;
	retval->head = 0;
	retval->buffer = malloc(sizeof(uint8_t)*capacity);
	return retval;
}

void destroyRingBuffer(RingBuffer *ringBuffer) {
	free(ringBuffer->buffer);
	free(ringBuffer);
}