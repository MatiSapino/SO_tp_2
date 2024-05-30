include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c)
SOURCES_ASM=$(wildcard asm/*.asm)
PROGRAMS_SOURCE=$(shell find ./programs/*/ -name "*.c")
PROGRAMS_OBJ=$(PROGRAMS_SOURCE:.c=.o)
LIB_SOURCE=$(shell find ./library/ -name "*.c")
LIB_OBJ=$(LIB_SOURCE:.c=.o)
SOURCES_SHARED=$(wildcard ../../Lib/*.c)
SHARED_OBJ=$(SOURCES_SHARED:.c=.o)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS) $(OBJECTS_ASM) $(PROGRAMS_OBJ) $(SHARED_OBJ) $(LIB_OBJ)  _loader.o
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld _loader.o $(OBJECTS) $(OBJECTS_ASM) $(PROGRAMS_OBJ) $(SHARED_OBJ) $(LIB_OBJ) -o ../$(MODULE)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld --oformat=elf64-x86-64 _loader.o $(OBJECTS) $(OBJECTS_ASM) $(PROGRAMS_OBJ) $(SHARED_OBJ) $(LIB_OBJ) -o ../0000-sampleCodeModule.elf

_loader.o: _loader.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -I./include/asm -I./include/library -I./include/programs/ipc -I./include/programs/mem -I./include/programs/pipe -I./include/programs/processes -I./include/programs/semaphore -I./include/programs/shell -I./include/programs/snake -I../../Lib/include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o programs/*/*.o library/*.o ../../Lib/*.o *.o *.bin *.elf ../*.elf

.PHONY: all clean print