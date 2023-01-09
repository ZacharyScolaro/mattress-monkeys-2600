bouncers: *.c
	arm-none-eabi-gcc -r -mlong-calls -fno-exceptions -march=armv6-m *.c -obouncers.bin -O2 -Wall -lgcc
	arm-none-eabi-strip bouncers.bin -d -R.comment -R.ARM.attributes
	../../Gopher2600/gopher2600 bouncers.bin
