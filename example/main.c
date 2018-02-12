#include <ring_buffer.h>
//#include <avr/io.h>

int main() {
	char buffer[10];
	RingBuffer ringBuffer = createRingBuffer(10, buffer);
	while(1) {

	}
}