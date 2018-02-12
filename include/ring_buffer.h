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

/**
	Read a value from the provided ring buffer
	@param {RingBuffer*} ringBuffer The buffer from which to read the value
	@param (uint8_t*) value Pointer to location to place output value
	@return 0 if successful, -1 if failed
*/
extern int8_t readRingBuffer(RingBuffer *ringBuffer, uint8_t *value);
/**
	Write a value to the provided ring buffer
	@param {RingBuffer*} ringBuffer The buffer to which the value will be written
	@param (uint8_t) value The value to write
	@return 0 if successful, -1 if failed
*/
extern int8_t writeRingBuffer(RingBuffer *ringBuffer, uint8_t value);
/**
	Create a ring buffer
	@param {uint8_t} capacity The desired capacity of the buffer
	@return A pointer to a new ring buffer if successful
*/
extern struct RingBuffer* createRingBuffer(uint8_t capacity);
/**
	Destroy a ring buffer
	@param {RingBuffer**} ringBufferPointerAddress A pointer to a pointer of the ring buffer to destroy
	@return 0 if successful, -1 if failed
*/
extern int8_t destroyRingBuffer(RingBuffer **ringBufferPointerAddress);
#endif