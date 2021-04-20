#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char* iniciar(char* tarea, double dificultad) {
    pid_t pid;
    int MeeseeksPadre;
    pid = fork();

    if (pid == 0) {
        MeeseeksPadre = getpid();
        printf("Hi I'm Mr. Meeseeks! Look at Meeee. (pid: %d, ppid: %d, N: %d, i: %d)\n",
            getpid(),
            getppid(),
            0,
            0);
        
    }
}