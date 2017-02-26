OBJECTS=$(wildcard *.c)

GCC_DIR =  /c/ti/msp430_gcc/bin
SUPPORT_FILE_DIRECTORY = /c/ti/msp430_gcc/include

DEVICE  = msp430g2553
CC      = $(GCC_DIR)/msp430-elf-gcc

CC 		= msp430-gcc

MSPDEBUG = ../mspdebug/mspdebug.exe

CFLAGS = -I $(SUPPORT_FILE_DIRECTORY) -mmcu=$(DEVICE) -O2 -g -Iinclude
LFLAGS = -L $(SUPPORT_FILE_DIRECTORY)
CFLAGS = -mmcu=$(DEVICE) -O2 -g -Iinclude -std=c99
LFLAGS = 

all: ${OBJECTS}
	$(CC) $(CFLAGS) $(LFLAGS) $? -o a.out

upload: 
	$(MSPDEBUG) -s COM7 tilib "prog a.out" "run"

clean:
	rm -f *.dat
	rm -f *.o