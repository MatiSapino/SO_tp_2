#define MAX_PHILOSOPHERS 10
#define MIN_PHILOSOPHERS 1
#define START_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int num_philosophers;

int left(int i){
    return (i + num_philosophers - 1) % num_philosophers;           // no puedo hacerlo un define porque varia la cantida de filos
}

int right(int i){
    return (i + 1) % num_philosophers;
}

int start_philos_dining(){
    num_philosophers = 0;   
    // aca abrir el semaforo




}