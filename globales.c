#include <semaphore.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct globales
{
    sem_t tareaFinalizada;

    int meeseeksIniciados;
    int meeseeksFinalizados;
}globales;


void initSem(sem_t* semaforo, char nombre[]) {
    semaforo = sem_open(nombre, O_CREAT, S_IRUSR | S_IWUSR, 0);
    sem_unlink(nombre); //Previene que exista siempre en caso de cromar
}

void destruirSemPadre(sem_t* semaforo, char nombre[]) {
    sem_close(semaforo);
}
void bloquerSemaforo(sem_t* semaforo) {
    sem_wait(semaforo);
}

void desbloquearSemaforo(sem_t* semaforo) {
    sem_post(semaforo);
}

/*
No se su formato pero esta mauren solo guarda el valor del semaforo en la variable valorSem,
es un puntero solamente para guardar el valor en esa variable, no es una lista
*/
int obtenerValorSemaforo(sem_t* semaforo) {
    int valorSem;
    sem_getvalue(semaforo, valorSem);
    return valorSem;
}

void generatePipe(int* fd) {
    pipe(fd);
}

void writeToPipe(int* fd, char message[]) {
    close(fd[0]);
    write(fd[1], message, sizeof(message));
    close(fd[1]);
}

void readFromPipe(int* fd, char *message) {
    close(fd[1]);
    read(fd[0], message, sizeof(message));
    close(fd[0]);
}

void openNamedPipePadre(int* fd, char nombre[]) {
    fd = open(nombre, O_RDONLY);
}

void openNamedPipeHijos(int* fd, char nombre[]) {
    fd = open(nombre, O_WRONLY);
}




// void compartirMemoria(globales *glob) { //Memoria compartida
//     key_t shmKey;
//     int shmId;

//     shmKey = ftok(".", 'x');
//     shmId = shmget(shmKey,sizeof(globales), IPC_CREAT | 0666);
//     glob = (globales *)shmat(shmId, NULL, 0);
// }

// void liberarMemoriaPadre(globales *glob) {// Memoria Compartida
//     key_t shmKey;
//     int shmId;

//     shmKey = ftok(".", 'x');
//     shmId = shmget(shmKey,sizeof(globales), IPC_CREAT | 0666);
//     shmdt((void *) glob); // Quita el vinculo de la memoria
//     shmctl(shmId, IPC_RMID, NULL); // Elimina la memoria compartida
// }

// void liberarMemoriaHijo(globales *glob) {// Memoria Compartida
//     shmdt((void *) glob); // Quita el vinculo de la memoria compartida
// }