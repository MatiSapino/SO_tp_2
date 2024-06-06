#include <testLinkedList.h>
#include <linkedList.h>
#include <assert.h>
#include <stdlib.h>
#include <video.h>

void test_linked_list(){
    
    list_ptr list = new_linked_list(NULL);
    add(list,"Alfredo");
    add(list,"Carlota");
    add(list,"Beatriz");
    add(list,"Dario");

    to_begin(list);

    while (hasNext(list))
    {
        puts((char *)next(list));
    }
    
    add(list,"Emilio");
    add(list,"Fernanda");

    to_begin(list);

    puts("____________________________________");
    while (hasNext(list))
    {
        puts((char *)next(list));
    }
}