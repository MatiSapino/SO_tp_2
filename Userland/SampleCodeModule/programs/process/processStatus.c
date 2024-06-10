#include <mem.h>
#include <process.h>
#include <std_io.h>
#include <processStatus.h>

static void draw_header() {
    own_printf("%4s %8s %8s %5s  %5s %10s %5s %10s %8s\n", "PID", "NAME", "STATE", "FG",
           "PRIO", "PARENT", "CHLD", "STACK", "BP");
}

int processStatus(int argc, char *argv[]) {

    char *status[] = {"WAITING", "READY", "TERM"};
    process_table_t *process_table = call_malloc(sizeof(process_table_t));

    call_get_process_table(process_table);

    int foreground = call_get_process_foreground();
    char *foreground_str;

    draw_header();

    for (size_t i = 0; i < process_table->count; i++) {
        if (process_table->entries[i].pid == foreground) {
            foreground_str = "YES";
        } else {
            foreground_str = "NO";
        }
        own_printf("%4d %8s %8s %6s %5d %10s %5d 0x%8x 0x%8x\n",
               process_table->entries[i].pid,
               process_table->entries[i].name,
               status[process_table->entries[i].status],
               foreground_str,
               process_table->entries[i].priority,
               process_table->entries[i].parent_name,
               process_table->entries[i].children_count,
               process_table->entries[i].stack, process_table->entries[i].rbp);
    }

    call_free(process_table);

    return 0;
}
