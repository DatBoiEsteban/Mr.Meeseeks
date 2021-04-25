#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>

#define NAME "/MeeseeksBox"

/*
This struct will contain the global values needed for process comunication, besides the one-to-one pipes.
The data includes: Amount of Mr.Meeseeks created (meeseeksIniciados), pId (pidMeeseekFinalizado) , ppId (ppidMeeseekFinalizado), 
N (nMeeseekFinalizado) and i (iMeeseekFinalizado) of the Mr.Meeseek who complete the request.  
*/
typedef struct globales
{
    sem_t tareaFinalizada;
    int meeseeksIniciados;
    pid_t pidMeeseekFinalizado;
    pid_t ppidMeeseekFinalizado;
    int nMeeseekFinalizado;
    int iMeeseekFinalizado;
    int bloqueo;
} globales;

/*
Initializes the semaphore
@param: semaphore, type of semaphore
@return: void
*/
void initSem(sem_t *semaforo, int tipo)
{
    sem_init(semaforo, tipo, 0);
}

/*
Changes the state of semaphore to 1 (blocked)
@param: semaphore
@return: void
*/
void bloquearSemaforo(sem_t *semaforo)
{
    sem_trywait(semaforo);
}

/*
Changes the state of semaphore to 0 (unblocked)
@param: semaphore
@return: void
*/
void desbloquearSemaforo(sem_t *semaforo)
{
    sem_post(semaforo);
}

/*
Gets the current state of the semaphore
@param: semaphore
@return: value of the state (0 or 1)
*/
int obtenerValorSemaforo(sem_t *semaforo)
{
    int valorSem = 0;
    sem_getvalue(semaforo, &valorSem);
    return valorSem;
}

/*
Creates a pipe
@param: pointer to file descriptor
@return: void
*/
void generatePipe(int *fd)
{
    pipe(fd);
}

/*
Write a message to the pipe
@param: pointer to file descriptor, message
@return: void
*/
void writeToPipe(int *fd, char message[])
{
    close(fd[0]);
    write(fd[1], message, sizeof(char) * 256);
    close(fd[1]);
}

/*
Read a message from the pipe
@param: pointer to file descriptor, pointer to a place for save the message
@return: void
*/
void readFromPipe(int *fd, char *message)
{
    close(fd[1]);
    read(fd[0], message, sizeof(char) * 256);
    close(fd[0]);
}

/*
Initializes the shared memory with the struct containing the global variables
@param: pointer to the struct
@return: void
*/
globales *compartirMemoria(int *fd)
{
    int desc = shm_open(NAME, O_CREAT | O_RDWR, 0600);
    fd = &desc;
    ftruncate(desc, sizeof(globales));
    globales *glob = (globales *)mmap(0, sizeof(globales), PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
    glob->bloqueo = 0;
    glob->iMeeseekFinalizado = 0;
    glob->meeseeksIniciados = 0;
    glob->nMeeseekFinalizado = 0;
    glob->pidMeeseekFinalizado = 0;
    glob->ppidMeeseekFinalizado = 0;
    return glob;
}

/*
Detaches the shared memory and errase the file
@param: file descriptor, global variables
@return: void
*/
void cerrarMemoria(int *fd, globales *glob)
{
    munmap(glob, sizeof(globales));
    close(*fd);
}

/*
Detaches the shared memory from the child process
@param: file descriptor, global variables
@return: void
*/
void cerrarMemoriaHijo(int *fd, globales *glob)
{
    cerrarMemoria(fd, glob);
    shm_unlink(NAME);
}

/*
Attaches a process to the shared memory
@param: file descriptor
@return: ponter to the global variables
*/
globales *unirseAMemoria(int *fd)
{
    int desc = shm_open(NAME, O_RDWR, 0666);
    fd = &desc;
    return (globales *)mmap(0, sizeof(globales), PROT_READ | PROT_WRITE, MAP_SHARED, desc, 0);
}
