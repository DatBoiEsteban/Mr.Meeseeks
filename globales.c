#include <semaphore.h>

typedef struct globales
{
    sem_t sem;
}globales;


int init_sem(globales* glob, int tipo) {
    return sem_init(&glob->sem, tipo, 1);
}