CC=arm-none-eabi-g++
CFLAGS=-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -specs=nosys.specs
CPPFLAGS=-DSTM32F411xE \
				 -I../../vendor/CMSIS/Device/ST/STM32F4/Include \
				 -I../../vendor/CMSIS/CMSIS/Core/Include

LINKER_FILE=../../linker_script.ld
LDFLAGS=-T $(LINKER_FILE) -u _printf_float

BINARY = cfw.elf

PROGRAMMER = openocd
PROGRAMMER_FLAGS = -f interface/stlink.cfg -f target/stm32f4x.cfg

all: $(BINARY)

$(BINARY): main.o syscalls.o USART.o GPIO.o startup.o system_stm32f4xx.o Timer.o Clock.o
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o $(BINARY)

main.o: main.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) main.cpp -c

syscalls.o: syscalls.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) syscalls.cpp -c

GPIO.o: GPIO.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) GPIO.cpp -c

USART.o: USART.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) USART.cpp -c
	
Timer.o: Timer.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) Timer.cpp -c

Clock.o: Clock.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) Clock.cpp -c

startup.o: ../../startup.cpp
	$(CC) $(CFLAGS) $(CPPFLAGS) ../../startup.cpp -c

system_stm32f4xx.o: ../../vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) $(CPPFLAGS) ../../vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c -c

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	del /F /Q *.o *.elf *.bin
else
	rm -f *.o *.elf *.bin
endif

flash: $(BINARY)
ifeq ($(OS),Windows_NT)
	arm-none-eabi-objcopy -O binary $(BINARY) cfw.bin
	powershell -Command "dfu-util -v -d 0483:df11 -a 0 -s 0x08000000:leave -D cfw.bin"
else
	arm-none-eabi-objcopy -O binary $(BINARY) cfw.bin
	dfu-util -v -d 0483:df11 -a 0 -s 0x08000000:leave -D cfw.bin
endif