// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <phylo.h>
#include <std_io.h>
#include <std_lib.h>
#include <string_s.h>
#include <userland_semaphore.h>

#define MAX_PHYLO 16
#define N         5
#define THINKING  '.'
#define HUNGRY    '.'
#define EATING    'E'

char state[MAX_PHYLO + 1];
sem_ptr state_sem;
sem_ptr mutex;

sem_ptr s[MAX_PHYLO];
char *args[MAX_PHYLO];
char name[32];

int pid[MAX_PHYLO];
int phylo_count;

int quit;

void philosopher(int argc, char *argv[]);
void pick_forks(int i);
void put_forks(int i);
void test(int i);
void printState();
int left(int i);
int right(int i);
void add_phylo();
void remove_phylo();
void exit_philosohpers();
void initialize_phylo();

void initialize_phylo() {
    quit = 0;
    for (int i = 0; i < N; i++) {
        char aux[8];
        itoa(i, aux, 10);
        strcpy(name + 10, aux);
        s[i] = call_sem_open(name, 0);
        char *argv[1];
        argv[0] = aux;
        pid[phylo_count++] = call_run(philosopher, 1, argv);
    }
}

int left(int i) {
    return (i + phylo_count - 1) % phylo_count;
}

int right(int i) {
    return (i + 1) % phylo_count;
}

void test(int i) {
    if (state[i] == HUNGRY && state[left(i)] != EATING &&
        state[right(i)] != EATING) {
        state[i] = EATING;
        printState();
        call_sem_post(s[i]);
    }
}

void printState() {
    call_sem_wait(state_sem);
    own_printf("%s\n", state);
    call_sem_post(state_sem);
}

void pick_forks(int i) {
    call_sem_wait(mutex);
    state[i] = HUNGRY;
    test(i);
    call_sem_post(mutex);
    call_sem_wait(s[i]);
}

void put_forks(int i) {
    call_sem_wait(mutex);
    state[i] = THINKING;
    test(left(i));
    test(right(i));
    call_sem_post(mutex);
}

void aux_sleep() {
    for (int i = 0; i < 10000000; i++) {
    }
}

void philosopher(int argc, char *argv[]) {
    int i = (int)strtol(argv[0], NULL, 10);
    while (!quit) {
        aux_sleep();
        pick_forks(i);
        aux_sleep();
        put_forks(i);
    }
    exit_philosohpers();
}

void receptionist() {
    int c, exit_loop = 1;
    while((c = getchar()) != EOF && exit_loop){
        switch (c)
        {
        case 'A':
        case 'a':
            add_phylo();
            break;
        case 'R':
        case 'r':
            remove_phylo();
            break;
        case 'Q':
        case 'q':
            exit_loop = 0;
           break;
            break;
        default:
            break;
        }
    }
}

int phylo_program(int argc, char *argv[]) {

    mutex = call_sem_open("mutex", 1);
    state_sem = call_sem_open("state_sem", 1);

    strcpy(name, "phylo_sem ");

    phylo_count = 0;

    initialize_phylo(); // creats first 5 philosophers

    call_run(receptionist, 0, NULL);

    call_wait();

    for (int i = 0; i < N; i++) {
        call_wait();
    }

    return 0;
}

void remove_phylo() {

    call_sem_wait(mutex);

    if (phylo_count == 1) {
        call_sem_post(mutex);
        return;
    }

    int phylo = phylo_count - 1;

    call_kill(pid[phylo]);
    call_sem_close(s[phylo]);

    phylo_count--;

    if (state[phylo] == EATING) {
        test(phylo - 1);
        test(0);
    }
    state[phylo] = '\0';
    own_printf("Philosopher removed\n");

    call_sem_post(mutex);
}

void add_phylo() {

    call_sem_wait(mutex);

    if (phylo_count == MAX_PHYLO) {
        call_sem_post(mutex);
        return;
    }

    char aux[8];
    itoa(phylo_count, aux, 10);
    strcpy(name + 10, aux);
    s[phylo_count] = call_sem_open(name, 0);
    char *argv[1];
    argv[0] = aux;
    pid[phylo_count++] = call_run(philosopher, 1, argv);
    own_printf("Philosopher added\n");

    call_sem_post(mutex);
}

void exit_philosohpers() {
    for (int i = 0; i < phylo_count; i++) {
        remove_phylo();
    }
    own_printf("Exiting program\n");
}
