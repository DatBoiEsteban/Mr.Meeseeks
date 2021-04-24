#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "globales.c"
#include "general.c"


void realizar(char *tarea, double dificultad, globales *glob, int nivel, int instancia)
{
    int cantHijos = intentarTarea(dificultad, glob->meeseeksIniciados);
    int valorSemaforo = obtenerValorSemaforo(&glob->tareaFinalizada);
    printf(" %d\n", cantHijos);
    if (valorSemaforo == 1 || cantHijos == 0)
    {
        if(valorSemaforo != 1) {
            bloquearSemaforo(&glob->tareaFinalizada);
        }
        glob->pidMeeseekFinalizado = getpid();
        glob->ppidMeeseekFinalizado = getppid();
        glob->nMeeseekFinalizado = nivel;
        glob->iMeeseekFinalizado = instancia;
        exit(0);
    }
    else
    {
        nivel++; // subimos de nivel porque pasamos a ser chamacos
        printf("%d\n", nivel);
        pid_t pid;
        if (0)
        {
            // Caos planetario
        }
        // int *pipesPorHijo = malloc(sizeof(int) * cantHijos);
        // int *pipePadre;
        int *pidHijos = malloc(sizeof(int) * cantHijos);
        for (int i = 0; i < cantHijos; i++)
        {
            int ins = i + 1;
            int fd[2];
            generatePipe(fd);
            pid = fork();

            if (pid == 0)
            {
                glob->meeseeksIniciados++;
                sayHiMrMeeseeks(nivel, ins);
                // pipePadre = fd;
                char *tareaARealizar = malloc(sizeof(char) * MAX_STRING_LENGTH);
                readFromPipe(fd, tareaARealizar);
                dificultad = diluirDificultad(dificultad, cantHijos);
                printf("%s\n", tareaARealizar);
                realizar(tareaARealizar, dificultad, glob, nivel, ins);
            }
            else
            {
                // pipesPorHijo[i] = fd;
                writeToPipe(fd, tarea);
                pidHijos[i] = pid;
            }
        }
        if (pid != 0)
        {
            while(wait(NULL) > 0){}
            exit(0);
        }
    }
}

char *realizarTarea(char *tarea, double dificultad)
{
    int nivel = 1;
    int instancia = 1;

    globales glob;
    compartirMemoria(&glob);
    initSem(&glob.tareaFinalizada, 1); // Tipo de semaforo 1 para procesos 0 para threads

    clock_t inicio_op = clock();
    double tiempo_op;
    pid_t pid = fork();

    if (pid == 0)
    {
        sayHiMrMeeseeks(nivel, instancia);
        glob.meeseeksIniciados++;
        realizar(tarea, dificultad, &glob, nivel, instancia);
    }
    else
    {
        wait(NULL);
        tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
    }

    return "holi"; // La salida formateada para la bitacora
}



char *ejecutarPrograma(char *programa)
{
    clock_t inicio_op = clock();
    double tiempo_op;
    int fd[2];
    generatePipe(fd);
    pid_t pid = fork();

    if (pid == 0)
    {
        int fallo = run(programa);

        // int fallo = system(programa);
        char *mes = malloc(sizeof(char) * 5);
        if (fallo == 0)
        {
            mes = "YES";
        }
        else
        {
            mes = "NO";
        }
        writeToPipe(fd, mes);
        exit(0);
    }
    else
    {
        char *mensaje = malloc(sizeof(char) * 512), *recibido = malloc(sizeof(char) * 5), *tiempo = malloc(sizeof(char) * 30);

        if (pid < 0)
        {
            //se despicho el fork
            printf("crome");
            exit(0);
        }
        else
        {
            // Meeseeks Box
            wait(&pid);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f.4", tiempo_op);
            readFromPipe(fd, recibido); // Agregar donde recibir el mensaje
        }
        strcat(mensaje, "Program executed: ");
        strcat(mensaje, programa);
        strcat(mensaje, ", Successful?: ");
        strcat(mensaje, recibido);
        strcat(mensaje, ", Time of execution: ");
        strcat(mensaje, tiempo);
        strcat(mensaje, "\n");
        return mensaje; // La salida formateada para la bitacora
    }
}

char *hacerLaMate(char *exp)
{
    clock_t inicio_op = clock();
    double tiempo_op;

    int fd[2];
    generatePipe(fd);
    pid_t pid = fork();
    if (pid == 0)
    {
        printf("Dani tambien me vendio");
        double resultado = hacerCalculos(exp);
        char *resulSTR = malloc(sizeof(char) * 30);
        sprintf(resulSTR, "%f.4", resultado);
        writeToPipe(fd, resulSTR); // Agregar el mensaje
        exit(0);
    }
    else
    {
        char *mensaje = malloc(sizeof(char) * 512), *recibido = malloc(sizeof(char) * 30), *tiempo = malloc(sizeof(char) * 30);

        if (pid < 0)
        {
            //se despicho el fork
            printf("crome");
            exit(0);
        }
        else
        {
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
}