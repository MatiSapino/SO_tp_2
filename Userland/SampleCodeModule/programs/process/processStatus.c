// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <mem.h>
#include <process.h>
#include <std_io.h>
#include <processStatus.h>

static void draw_header() {
    own_printf("%8s %12s %8s %5s %10s %5s %10s %8s\n", "PID", "NAME", "STATE",
           "PRIO", "PARENT", "CHLD", "STACK", "BP");
}

int ps(int argc, char *argv[]) {

    char *status[] = {"WAITING", "READY", "TERM"};
    process_table_t *process_table = call_malloc(sizeof(process_table_t));

    call_get_process_table(process_table);

    draw_header();
    for (size_t i = 0; i < process_table->count; i++) {
        own_printf("%8d %12s %8s %5d %10s %5d 0x%8x 0x%8x\n",
               process_table->entries[i].pid, process_table->entries[i].name,
               status[process_table->entries[i].status],
               process_table->entries[i].priority,
               process_table->entries[i].parent_name,
               process_table->entries[i].children_count,
               process_table->entries[i].stack, process_table->entries[i].rbp);
    }

    call_free(process_table);

    return 0;
}
