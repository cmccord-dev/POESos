OBJECTS=$(wildcard *.c)

GCC_DIR =  /c/ti/msp430_gcc/bin
SUPPORT_FILE_DIRECTORY = /c/ti/msp430_gcc/include

DEVICE  = msp430g2553
CC      = $(GCC_DIR)/msp430-elf-gcc
GDB     = $(GCC_DIR)/msp430-elf-gdb

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g -Iinclude
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o a.out

upload: 
	../../mspdebug/mspdebug.exe -s COM5 tilib "prog a.out" "run"

clean:
	rm -f *.dat
	rm -f *.o