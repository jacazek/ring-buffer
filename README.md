# ring-buffer

Library for creating a uint8_t ring buffer

## Build
From the root of the project run `make` to make the library

From the root of the project run `make tests` to run the tests

## Use
Copy the /dist/* directory to the project that would reference the library

If using the buffer for host (x86) then include the `/lib/` directory as a library directory `-L/lib/` build argument

If using the buffer for atmel mcu then include the `/lib-avr/` directory as a library directory `-L/lib-avr/` build argument

Include the library `-lring_buffer` as a build argument
