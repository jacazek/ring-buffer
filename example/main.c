#include <ring_buffer.h>
//#include <avr/io.h>
static char buffer[8];

int main() {
	RingBuffer ringBuffer = createRingBuffer(8, buffer);
	while(1) {

	}
}