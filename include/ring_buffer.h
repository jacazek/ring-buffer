#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_
#include <stdint.h>
typedef struct RingBuffer {
	uint8_t capacity;
	uint8_t filled;
	uint8_t head;
	uint8_t tail;
	char *buffer;
} RingBuffer;

extern int8_t readRingBuffer(RingBuffer *ringBuffer, uint8_t *value);
extern int8_t writeRingBuffer(RingBuffer *ringBuffer, uint8_t value);
extern struct RingBuffer* createRingBuffer(uint8_t capacity);
extern int8_t destroyRingBuffer(RingBuffer **ringBufferPointerAddress);
#endif