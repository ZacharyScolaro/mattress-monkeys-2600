mattress_monkeys: *.cpp assets
	arm-none-eabi-g++ -r -mlong-calls -fno-exceptions -march=armv6-m *.cpp -oMattressMonkeys.bin -O3 -Wall -LvcsLib/lib -lgcc -lFP32 -IvcsLib/inc
	arm-none-eabi-strip MattressMonkeys.bin -d -R.comment -R.ARM.attributes
	# Build with mock to catch any missing symbol definitions that won't be provided by the firmware
	arm-none-eabi-g++ -mlong-calls -fno-exceptions --specs=nosys.specs -march=armv6-m MattressMonkeys.bin -omocked.bin -O3 -Wall -LvcsLib/lib -lvcsMock -lgcc
	cp MattressMonkeys.bin ../../ChameleonCartFirmware/Core/Lib/libelfrom.a
	touch ../../ChameleonCartFirmware/Core/Src/main.c
	../../gopher2600_linux_amd64 MattressMonkeys.bin

assets: ../assets/* kernel_7800.asm
	dasm "kernel_7800.asm" -f3 "-okernel_7800.bin" "-lkernel_7800.lst" "-skernel_7800.sym" -v4 -p10
	python3 parse_assets.py

