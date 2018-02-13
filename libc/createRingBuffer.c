#include <ring_buffer.h>

RingBuffer createRingBuffer(uint8_t capacity, char *buffer) {
	RingBuffer retval;
	retval.settings = (1<<OVERWRITE_EN);
	retval.capacity = capacity;
	retval.filled = 0;
	retval.head = 0;
	retval.buffer = buffer;
	return retval;
}