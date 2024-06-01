#include <buffer.h>

#define MAX_ARGC 5
#define TOKEN_LENGTH   512


typedef struct cmd {
    char *name;
    char *argv[MAX_ARGC];
    int argc;
} cmd_t;

typedef struct line {
    char operator; // '|' or '&'
    cmd_t *left_cmd;
    cmd_t *right_cmd;
} line_t;

typedef int (*function_t)(int, char *[]);

typedef struct cmd_entry {
    char *name;
    function_t function;
} cmd_entry_t;

sem_ptr sem_pipe_exec;
static char whitespace[] = " \t\n";
static char operators[] = "|&";

cmd_entry_t cmd_table[] = {{"help", help},
                           {NULL, NULL}};

void clearBuffer(char *buff)
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buff[i] = 0;
    }
}

static int gettoken(char **src, char *token, char *delimiters) {
    enum {
        START,
        STEP,
        DELIM,
        ERROR
    } state = START;

    size_t i = 0;

    if (**src == '\0')
        return -1;

    while (**src != '\0') {
        switch (state) {
            case START:
                // ignore whitespaces
                if (strchr(whitespace, **src))
                    (*src)++;

                // if delimiter is found at first, go to error
                else if (strchr(delimiters, **src))
                    state = ERROR;

                // if letter is found, go to next step
                else
                    state = STEP;

                break;
            case STEP:
                // fill the buffer until delimiter
                if (!strchr(delimiters, **src))
                    token[i++] = *(*src)++;

                else
                    state = DELIM;

                break;
            case DELIM:
                token[i] = '\0';
                return *(*src)++;
            case ERROR:
                return -1;
            default:
                break;
        }
    }

    token[i] = '\0';
    return *(*src);
}

static cmd_t *parsecommand(char *input) {
    char *cmdidx = input;
    char token[TOKEN_LENGTH] = {0};

    cmd_t *cmd =call_malloc(sizeof(cmd_t));
    cmd->argc = 0;

    // get the name of the command;
    gettoken(&cmdidx, token, whitespace);
    cmd->name = call_malloc(strlen(token) + 1);
    strcpy(cmd->name, token);

    cmd->argv[cmd->argc] = call_malloc(strlen(token) + 1);
    strcpy(cmd->argv[cmd->argc], token);
    cmd->argc++;

    token[0] = '\0';
    while (gettoken(&cmdidx, token, whitespace) != -1 && cmd->argc < MAX_ARGC) {
        cmd->argv[cmd->argc] = call_malloc(strlen(token) + 1);
        strcpy(cmd->argv[cmd->argc], token);
        cmd->argc++;
        token[0] = '\0';
    }

    return cmd;
}

static line_t *parseline(char *line) {

    char *l = line;
    char chunk[TOKEN_LENGTH] = {0};

    line_t *pline = call_malloc(sizeof(line_t));
    pline->left_cmd = NULL;
    pline->right_cmd = NULL;
    pline->operator= 0;

    int delim = 0;

    while ((delim = gettoken(&l, chunk, operators)) != -1) {
        switch (delim) {
            case '|':
                if (pline->operator)
                    break;

                pline->operator= '|';
                pline->left_cmd = parsecommand(chunk);
                break;
            case '&':
                if (pline->operator)
                    break;

                pline->operator= '&';
                pline->left_cmd = parsecommand(chunk);
                break;
            case '\0':
                if (pline->operator== '|')
                    pline->right_cmd = parsecommand(chunk);

                else if (pline->operator!= '&')
                    pline->left_cmd = parsecommand(chunk);

                break;
            default:
                break;
        }
    }

    return pline;
}

static function_t get_cmd(char *cmd_name) {
    for (int i = 0; cmd_table[i].name != NULL; i++) {
        if (!strCompare(cmd_name, cmd_table[i].name)) {
            return cmd_table[i].function;
        }
    }

    return NULL;
}


static void pipe_exec_left(int argc, char *argv[]) {

    function_t function = get_cmd(argv[0]);

    int fd[2];
    call_sem_wait(sem_pipe_exec);
    if (call_create_pipe("shell_pipe", fd) == -1)
        call_open_pipe("shell_pipe", fd);
    call_sem_post(sem_pipe_exec);

    call_dup2(fd[1], 1);
    call_close(fd[1]);
    call_close(fd[0]); // close read

    function(argc, argv);
}

static void pipe_exec_right(int argc, char *argv[]) {

    function_t function = get_cmd(argv[0]);

    int fd[2];
    call_sem_wait(sem_pipe_exec);
    if (call_open_pipe("shell_pipe", fd) == -1)
        call_create_pipe("shell_pipe", fd);
    call_sem_post(sem_pipe_exec);

    call_dup2(fd[0], 0);
    call_close(fd[0]);
    call_close(fd[1]); // close write

    function(argc, argv);
}

static void pipe_exec(cmd_t *left, cmd_t *right) {
    sem_pipe_exec = call_sem_open("shell_sem_pipe_exec", 1);
    int left_pid = call_run(pipe_exec_left, left->argc, left->argv);
    int right_pid = call_run(pipe_exec_right, right->argc, right->argv);
    call_waitpid(left_pid, NULL);
    call_waitpid(right_pid, NULL);
    call_sem_close(sem_pipe_exec);
}

static void invalid_command(char *cmd_name) {
    own_printf("[ Command %s not found ]\n", cmd_name);
}

static int run_command(char *name, int argc, char *argv[]) {

    function_t function = get_cmd(name);

    if (function == NULL) {
        invalid_command(name);
        return -2;
    }

    return call_run(function, argc, argv);
}

static int background_exec(int argc, char *argv[]) {

    function_t function = get_cmd(argv[0]);

    if (function == NULL)
        call_exit(-1);

    call_close(0);
    call_close(1);

    function(argc, argv);

    return 0;
}

void freecmd(cmd_t *cmd) {
    if (cmd == NULL)
        return;

    for (size_t i = 0; i < cmd->argc; i++)
        call_free(cmd->argv[i]);

    call_free(cmd->name);
    call_free(cmd);
}

void freepline(line_t *parsedline) {
    freecmd(parsedline->left_cmd);
    freecmd(parsedline->right_cmd);
    call_free(parsedline);
}

void read_buffer(int *screenIndx, char screen[], char buffer[], int *status)
{
    int i = 0;
    int end_of_buffer = 0;
    int flag = 0;
    while (i < BUFFER_SIZE)
    {
        char c = getC();
        end_of_buffer = (i == BUFFER_SIZE - 1);
        if (c == '\b')
        {
            if (i > 0 && *screenIndx > 0)
            {
                i--;
                screen[(*screenIndx)--] = 0;
                screen[(*screenIndx)--] = 0;
            }
            else
                flag = 1;
        }
        else if (c == '\n')
        {
            removeCursor();
            putC(c, GREEN);
            buffer[i] = 0;
            if (*buffer != 0)
            {
                int pid = -1, proc_status = -1;
                line_t *parsedline = parseline(buffer);

                switch (parsedline->operator) {
                    case '|':
                        pipe_exec(parsedline->left_cmd, parsedline->right_cmd);
                        break;
                    case '&':
                        run_command("background_exec", parsedline->left_cmd->argc,
                                    parsedline->left_cmd->argv);
                        break;
                    default:
                        pid = run_command(parsedline->left_cmd->name,
                                        parsedline->left_cmd->argc,
                                        parsedline->left_cmd->argv);
                        call_setfg(pid);
                        call_waitpid(pid, &proc_status);
                        break;
                }

                freepline(parsedline);
            }
            if (*status)
                putLine();
            clearBuffer(buffer);
            return;
        }
        else if (c == '-')
        {
            removeCursor();
            putNewLine();
            own_printf("snapshot taken!");
            putNewLine();
            putLine();
            flag = 1;
        }
        else if (c != '-')
        {
            if (!end_of_buffer)
                buffer[i++] = c;
            else
                flag = 1;
        }
        if (!flag)
        {
            removeCursor();
            putC(c, GREEN);
            putCursor();
        }

        flag = 0;
    }
    return;
}