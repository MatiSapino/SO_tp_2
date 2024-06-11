include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(shell find . -name "*.c")
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS)
	$(LD) $(LDFLAGS) -T kernel.ld --oformat=elf64-x86-64 -o kernel.elf $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) 

%.o: %.c
	$(GCC) $(GCCFLAGS) $(MEMFLAGS) -I./include -I./include/drivers -I./include/graphics -I./include/interrupts -I./include/interrupts/exceptions -I./include/interrupts/idt -I./include/interrupts/syscalls -I./include/interrupts/time -I./include/lib -I./include/mem -I./include/pipe -I./include/process -I./include/semaphore -I./include/test -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o drivers/*.o graphics/*.o interrupts/*.o interrupts/*/*.o lib/*.o mem/*.o pipe/*.o process/*.o semaphore/*.o test/*.o *.o *.bin *.elf

.PHONY: all clean
