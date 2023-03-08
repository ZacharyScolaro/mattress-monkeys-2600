bouncers: *.c assets
	arm-none-eabi-gcc -r -mlong-calls -fno-exceptions -march=armv6-m *.c -obouncers.bin -O3 -Wall -lgcc
	arm-none-eabi-strip bouncers.bin -d -R.comment -R.ARM.attributes
	cp bouncers.bin ../../ChameleonCartFirmware/Core/Lib/libelfrom.a
	touch ../../ChameleonCartFirmware/Core/Src/main.c
	../../Gopher2600/gopher2600 bouncers.bin

assets: ../assets/* kernel_7800.asm
	dasm "kernel_7800.asm" -f3 "-okernel_7800.bin" "-lkernel_7800.lst" "-skernel_7800.sym" -v4 -p10
	python3 parse_assets.py

