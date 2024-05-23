include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard [^_]*.c library/*.c programs/mem/*.c programs/processes/*.c programs/shell/*.c programs/snake/*.c)
LIBRARIES=$(wildcard libraries/*.c)

SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_ASM=$(SOURCES_ASM:asm/%.asm=obj/%.asm.o)

INCLUDE_PATHS = -I ./include -I ./include/asm -I ./include/library -I ./include/programs/mem -I ./include/programs/processes -I ./include/programs/shell -I ./include/programs/snake

all: $(MODULE)

$(MODULE): $(SOURCES) $(OBJECTS_ASM)
	$(GCC) $(GCCFLAGS) $(INCLUDE_PATHS) -T sampleCodeModule.ld _loader.c $(OBJECTS_ASM) $(SOURCES) -o ../$(MODULE)

obj/%.asm.o : asm/%.asm
	mkdir -p obj
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o
	rm -rf obj

.PHONY: all clean print