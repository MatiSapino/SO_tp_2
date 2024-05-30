#include <infoPipe.h>

int columns[7];

static void print_tabs(int amount)
{
    char buffer[80] = {0};
    int i = 0;
    while (i < amount)
    {
        buffer[i++] = ' ';
    }
    own_printf("%s", buffer);
}

static void print_header()
{
    own_printf("NAME           | BLOCKED | BLOCKED PIDS      | R_OPEN  | W_OPEN  | R   | W   \n");
}

static int get_spaces(char *str, int col)
{
    return columns[col] - strlen(str);
}

static void pids_to_str(int pids[], char dest[], int size)
{

    int i = 0;
    for (int j = 0; i < size; j++)
    {
        char aux[8] = {0};
        itoa(pids[j], aux, 10);
        int k = 0;
        while (aux[k] != 0)
        {
            dest[i++] = aux[k++];
        }
        dest[i++] = ' ';
    }
    dest[i++] = '\0';
}

// static void print_line(pipe_t *info)
// {

//     char aux[80] = {0};

//     // NAME
//     int len = 0;
//     if ((len = strlen(info->name)) > columns[0])
//     {
//         strcpy(aux, info->name);
//         aux[columns[0] - 1] = '.';
//         aux[columns[0] - 2] = '.';
//         aux[columns[0] - 3] = '.';
//         aux[columns[0]] = '\0';
//         own_printf("%s ", aux);
//     }
//     else
//     {
//         own_printf("%s ", info->name);
//     }
//     print_tabs(get_spaces(info->name, 0));
//     own_printf("| ");

//     // BLOCKED
//     itoa(info->blocked_count, aux, 10);
//     own_printf("%s", aux);
//     print_tabs(get_spaces(aux, 1));
//     own_printf("| ");

//     // BLOCKED_PIDS
//     pids_to_str(info->blocked_pid, aux, info->blocked_count);
//     if (info->blocked_count == 0)
//     {
//         print_tabs(get_spaces("", 2));
//     }
//     else
//     {
//         own_printf("%s", aux);
//         print_tabs(get_spaces(aux, 2));
//     }
//     own_printf("| ");

//     // R_OPEN
//     itoa(info->readopen, aux, 10);
//     own_printf("%s", aux);
//     print_tabs(get_spaces(aux, 3));
//     own_printf("| ");

//     // W_OPEN
//     itoa(info->writeopen, aux, 10);
//     own_printf("%s", aux);
//     print_tabs(get_spaces(aux, 4));
//     own_printf("| ");

//     // R
//     itoa(info->nread, aux, 10);
//     own_printf("%s", aux);
//     print_tabs(get_spaces(aux, 5));
//     own_printf("| ");

//     // W
//     itoa(info->nwrite, aux, 10);
//     own_printf("%s", aux);
//     print_tabs(get_spaces(aux, 6));
//     putNewLine();
// }

static void init_columns_size()
{
    columns[0] = strlen("NAME          ");
    columns[1] = strlen(" BLOCKED");
    columns[2] = strlen(" BLOCKED PIDS     ");
    columns[3] = strlen(" R_OPEN ");
    columns[4] = strlen(" W_OPEN ");
    columns[5] = strlen(" R  ");
    columns[6] = strlen(" W  ");
}

// void info_pipe(char *name)
// {

//     pipe_t *pipe_info = (pipe_t *)call_malloc(sizeof(pipe_t));
//     call_info_pipe(name, pipe_info);

//     init_columns_size();
//     print_header();
//     print_line(pipe_info);

//     putNewLine();
// }

// int info_all_pipes(int argc, char *argv[])
// {

//     pipe_t *arr[MAX_PIPES] = {0};
//     for (int i = 0; i < MAX_PIPES; i++)
//     {
//         arr[i] = (pipe_t *)call_malloc(sizeof(pipe_t));
//     }
//     int amount = call_info_all_pipes(arr, MAX_PIPES);

//     init_columns_size();
//     print_header();

//     for (int i = 0; i < amount; i++)
//     {
//         print_line(arr[i]);
//     }

//     putNewLine();

//     for (int i = 0; i < MAX_PIPES; i++)
//     {
//         call_free(arr[i]);
//     }

//     return 0;
// }