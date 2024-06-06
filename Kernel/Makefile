include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(shell find . -name "*.c")
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_SHARED=$(wildcard ../Lib/*.c)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_SHARED=$(SOURCES_SHARED:.c=.o)
LOADERSRC=loader.asm
# Uncomment to use buddy memory allocator
# MEMFLAGS=-D BUDDY
MEMFLAGS=

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_SHARED)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(OBJECTS_SHARED)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(OBJECTS_SHARED)

%.o: %.c
	$(GCC) $(GCCFLAGS) $(MEMFLAGS) -I./include -I./include/drivers -I./include/graphics -I./include/interrupts -I./include/interrupts/exceptions -I./include/interrupts/idt -I./include/interrupts/syscalls -I./include/interrupts/time -I./include/library -I./include/memory -I./include/pipe -I./include/process -I./include/semaphore -I./include/test -I../Lib/include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o drivers/*.o interrupts/*/*.o library/*.o memory/*.o pipe/*.o process/*.o semaphore/*.o test/*.o ../../Lib/*.o *.o *.bin *.elf

.PHONY: all clean