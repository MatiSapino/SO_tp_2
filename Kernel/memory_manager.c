//RETORNA BLOQUES DE 1 BYTE, NO LIBERA MEMORIA

//ASUMO QUE LA MEMORIA LIBRE ARRANCA EN 0x900000 (9MB)
//PARA SABER ESTO HAY QUE LEER LA GUIA DE BUILDING (ver end_of_binary en el script de linkeo, es .ld)
#include "memory_manager.h"
#include "drivers/include/videoDriver.h"

//char my_memory[MEMORY_MANAGER_SIZE];
char *my_memory;
char *current;

//        [- - - - - - -] 
//  current^

//0 idt
//1MB kernel
//5MB userspace
//9MB memoria libre

void memory_manager_init() {
    my_memory = (char *)0x900000;
    current = my_memory;
}


void* my_malloc() {
    if (current < my_memory + MEMORY_MANAGER_SIZE)
        return current++;
    else
        return NULL;
}

//        [- - - - - - -] 
//    current^


char * memory_manager(char * buffer) {
    memory_manager_init();
    char *ptr = (char *) my_malloc();
    if (!ptr) drawWordColor(RED, "memory_manager ptr is NULL\n");
    *ptr = '5';
    buffer[0] = *ptr;
    return buffer;
}