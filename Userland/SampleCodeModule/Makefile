include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c library/*.c programs/*/*.c)
LIBRARIES=$(wildcard libraries/*.c)

SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_SHARED=$(wildcard ../../Lib/*.c)
OBJECTS_ASM=$(SOURCES_ASM:asm/%.asm=obj/%.asm.o)

INCLUDE_PATHS = -I ./include -I ./include/asm -I ./include/library -I ./include/programs/ipc -I ./include/programs/mem -I ./include/programs/pipe -I ./include/programs/processes -I ./include/programs/shell -I ./include/programs/snake -I ../../Lib/include

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) $(INCLUDE_PATHS) -T sampleCodeModule.ld _loader.c $(OBJECTS_ASM) $(SOURCES) $(SOURCES_SHARED) -o ../$(MODULE)

obj/%.asm.o : asm/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf obj
	rm -rf asm/*.o *.o *.bin
	rm -rf library/*.o *.o *.bin
	rm -rf programs/*.o *.o *.bin

.PHONY: all clean print