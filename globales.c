#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>

/*
This struct will contain the global values needed for process comunication, besides the one-to-one pipes.
The data includes: Amount of Mr.Meeseeks created (meeseeksIniciados), pId (pidMeeseekFinalizado) , ppId (ppidMeeseekFinalizado), 
N (nMeeseekFinalizado) and i (iMeeseekFinalizado) of the Mr.Meeseek who complete the request.  
*/
typedef struct globales
{
    sem_t tareaFinalizada;

    int meeseeksIniciados;
    int pidMeeseekFinalizado;
    int ppidMeeseekFinalizado;
    int nMeeseekFinalizado;
    int iMeeseekFinalizado;
}globales;

/*
Initializes the semaphore
@param: semaphore, type of semaphore
@return: void
*/
void initSem(sem_t* semaforo, int tipo) {
    return sem_init(semaforo, tipo, 0);
}

/*
Changes the state of semaphore to 1 (blocked)
@param: semaphore
@return: void
*/
void bloquearSemaforo(sem_t* semaforo) {
    sem_wait(semaforo);
}

/*
Changes the state of semaphore to 0 (unblocked)
@param: semaphore
@return: void
*/
void desbloquearSemaforo(sem_t* semaforo) {
    sem_post(semaforo);
}

/*
Gets the current state of the semaphore
@param: semaphore
@return: value of the state (0 or 1)
*/
int obtenerValorSemaforo(sem_t* semaforo) {
    int valorSem = 0;
    sem_getvalue(semaforo, valorSem);
    return valorSem;
}

/*
Creates a pipe
@param: pointer to file descriptor
@return: void
*/
void generatePipe(int* fd) {
    pipe(fd);
}

/*
Write a message to the pipe
@param: pointer to file descriptor, message
@return: void
*/
void writeToPipe(int* fd, char message[]) {
    close(fd[0]);
    write(fd[1], message, sizeof(message));
    close(fd[1]);
}

/*
Read a message from the pipe
@param: pointer to file descriptor, pointer to a place for save the message
@return: void
*/
void readFromPipe(int* fd, char* message) {
    close(fd[1]);
    read(fd[0], message, sizeof(message));
    close(fd[0]);
}

/*
Initializes the shared memory with the struct containing the global variables.
@param: pointer to the struct
@return: void
*/
void compartirMemoria(globales* glob) { 
    key_t shmKey;
    int shmId;

    shmKey = ftok(".", 'x');
    shmId = shmget(shmKey,sizeof(globales), IPC_CREAT | 0666);
    glob = (globales *)shmat(shmId, NULL, 0);
}

/*
Detach the memory of the parent process and remove the shared memory file
@param: pointer to shared memory
@return: void
*/
void liberarMemoriaPadre(globales *glob) {// Memoria Compartida
    key_t shmKey;
    int shmId;

    shmKey = ftok(".", 'x');
    shmId = shmget(shmKey,sizeof(globales), IPC_CREAT | 0666);
    shmdt((void *) glob); // Quita el vinculo de la memoria
    shmctl(shmId, IPC_RMID, NULL); // Elimina la memoria compartida
}

/*
Detach the shared mememory for a child process
@param: pointer to shared memory
@return: void
*/
void liberarMemoriaHijo(globales *glob) {// Memoria Compartida
    shmdt((void *) glob); // Quita el vinculo de la memoria compartida
}