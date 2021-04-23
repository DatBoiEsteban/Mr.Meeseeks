#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "globales.c"
#include "general.c"

char* realizarTarea(char* tarea, double dificultad) {
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

    return ""; // La salida formateada para la bitacora
}

char* ejecutarPrograma(char *programa, char *arg1, char *arg2) {
    
    clock_t inicio_op = clock();
    double tiempo_op;
    int fd[2];
    generatePipe(fd);
    int pid = fork();
    

    if(pid == 0) {
        int fallo = run(programa, arg1, arg2);

        if(fallo == -1) {
            writeToPipe(fd, "NO");
        } else {
            writeToPipe(fd, "YES");
        }
        
        exit(0);

    } else {
        char *mensaje = malloc(sizeof(char) * 512), *recibido = malloc(sizeof(char)*30), *tiempo = malloc(sizeof(char)*30);

        if(pid < 0) {
            //se despicho el fork
        } else {
            // Meeseeks Box
            wait(&pid);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f.4", tiempo_op);
            readFromPipe(fd, recibido); // Agregar donde recibir el mensaje
        }
        strcat(mensaje, "Program executed: ");
        strcat(mensaje, programa);

        if(arg1 != "") {
            strcat(mensaje, " ");
            strcat(mensaje, arg1);
        }

        if(arg2 != "") {
            strcat(mensaje, " ");
            strcat(mensaje, arg2);
        }

        strcat(mensaje, ", Successful?: ");
        strcat(mensaje, recibido);
        strcat(mensaje, ", Time of execution: ");
        strcat(mensaje, tiempo);
        strcat(mensaje, "\n");
        return mensaje; // La salida formateada para la bitacora
    }
}

char* hacerLaMate(char* exp) {
    clock_t inicio_op = clock();
    double tiempo_op;

    int fd[2];
    generatePipe(fd);
    int pid = fork();
    if(pid == 0) {
        
        double resultado = eval(exp);
        char *resulSTR = malloc(sizeof(char) * 30);
        sprintf(resulSTR,"%f.4", resultado);
        writeToPipe(fd, resulSTR);// Agregar el mensaje
        exit(0);
    } else {
        char *mensaje = malloc(sizeof(char) * 512), *recibido = malloc(sizeof(char)*30), *tiempo = malloc(sizeof(char)*30);

        if(pid < 0) {
            //se despicho el fork
            printf("crome");
        } else {
            // Meeseeks Box
            wait(&pid);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f.4", tiempo_op);
            readFromPipe(fd, recibido); // Agregar donde recibir el mensaje
        }
        strcat(mensaje, "Expression evaluated: ");
        strcat(mensaje, exp);
        strcat(mensaje, ", Value: ");
        strcat(mensaje, recibido);
        strcat(mensaje, ", Time of execution: ");
        strcat(mensaje, tiempo);
        strcat(mensaje, "\n");
        return mensaje; // La salida formateada para la bitacora
    }

    return ""; // La salida formateada para la bitacora
}