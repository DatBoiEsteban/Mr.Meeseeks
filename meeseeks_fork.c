#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#include "globales.c"

char* iniciar(char* tarea, double dificultad) {
    pid_t pid;
    int MeeseeksPadre;
    pid = fork();

    int nivel = 1;

    clock_t inicio_op = clock();
    double tiempo_op;
    if (pid == 0) {
        MeeseeksPadre = getpid();
        printf("Hi I'm Mr. Meeseeks! Look at Meeee. (pid: %d, ppid: %d, N: %d, i: %d)\n",
            getpid(),
            getppid(),
            nivel,
            0);
        while(1) {
            if(0) { // Hay que avisarle al tata que mate los hijos

            } else { // Logica de los chamacos
                int cantHijos = 0; // general.c obtener cantidad de hijos
                nivel++; // subimos de nivel porque pasamos a ser chamacos


                for (int i = 0; i < cantHijos; i++)
                {
                    pid = fork();

                    if (pid == 0){
                        // Lo que hagan los chamacos
                    } else {
                        // termina?
                    }
                }

                if(pid != 0){
                    while (wait(NULL) > 0){}
                    break;
                }
            }
        }
    } else {
        //Meeseeks Box
        tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;

    }
}