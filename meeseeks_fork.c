#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

#include "globales.c"
#include "general.c"
/*
Strategy of planetary Chaos, simulates random amount of processes (between 10000 to 150000)
@param: void
@return: void
*/
void caos()
{
    printf("CAOS PLANETARIO ");
    sleep(1);
    pid_t pid;
    for (int i = 0; i < generarRandom(10000, 15000); i++)
    {
        pid = fork();

        if (pid == 0)
        {
            sayHiMrMeeseeks(1, i + 1);
            exit(0);
        }
    }
    exit(0);
}

/*
Manages the processes for the textual request, in a recursive manner
@param: request, difficulty, level, instance, file descriptor and global variables
@return: void
*/
void realizar(char *tarea, double dificultad, int nivel, int instancia, int fd, globales *globThis)
{
    int cantHijos = intentarTarea(dificultad, globThis->meeseeksIniciados);
    if (cantHijos == 0 || globThis->bloqueo == 1)
    {

        if (obtenerValorSemaforo(&globThis->tareaFinalizada) == 0)
        {
            bloquearSemaforo(&globThis->tareaFinalizada);
            globThis->bloqueo = 1;
            desbloquearSemaforo(&globThis->tareaFinalizada);
            globThis->pidMeeseekFinalizado = getpid();
            globThis->ppidMeeseekFinalizado = getppid();
            globThis->nMeeseekFinalizado = nivel;
            globThis->iMeeseekFinalizado = instancia;
        }
        cerrarMemoriaHijo(&fd, globThis);
        exit(0);
    }
    else
    {
        nivel++; // subimos de nivel porque se pasa a los child process
        pid_t pid;
        int *pidHijos = malloc(sizeof(int) * cantHijos);
        for (int i = 0; i < cantHijos; i++)
        {
            int ins = i + 1;
            int fd[2];
            generatePipe(fd);
            pid = fork();

            if (pid == 0)
            {
                char *tareaARealizar = malloc(sizeof(char) * MAX_STRING_LENGTH);
                readFromPipe(fd, tareaARealizar);
                int fdm;
                globales *globHijo = unirseAMemoria(&fdm);
                globHijo->meeseeksIniciados++;
                sayHiMrMeeseeks(nivel, ins);
                dificultad = diluirDificultad(dificultad, cantHijos);
                realizar(tareaARealizar, dificultad, nivel, ins, fdm, globHijo);
            }
            else
            {
                writeToPipe(fd, tarea);
                pidHijos[i] = pid;
            }
        }
        if (pid != 0)
        {
            for (int i = 0; i < cantHijos; i++)
            {
                waitpid(pidHijos[i], 0, 0);
            }
            free(pidHijos);
            cerrarMemoriaHijo(&fd, globThis);
            exit(0);
        }
    }
}

/*
Performs the textual request
@param: request, difficulty
@return: message for the record
*/
char *realizarTarea(char *tarea, double dificultad)
{
    if (dificultad == 0)
    {
        caos();
    }
    else
    {
        int nivel = 1;
        int instancia = 1;
        int fd;
        globales *glob = compartirMemoria(&fd);
        initSem(&glob->tareaFinalizada, 1); // Tipo de semaforo 1 para procesos 0 para threads
        clock_t inicio_op = clock();
        double tiempo_op;
        pid_t pid = fork();
        char *mensaje = malloc(sizeof(char) * 512), *tiempo = malloc(sizeof(char) * 30);
        if (pid == 0)
        {
            int fd;
            globales *globhijo = unirseAMemoria(&fd);
            sayHiMrMeeseeks(nivel, instancia);
            globhijo->meeseeksIniciados++;
            realizar(tarea, dificultad, nivel, instancia, fd, globhijo);
        }
        else
        {
            while (glob->bloqueo == 0)
            {
            }
            wait(NULL);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f", tiempo_op);
            printf("Meeseek pid: %d, ppid: %d, n: %d, i: %d Ha completado la tarea en %fs\n", glob->pidMeeseekFinalizado, glob->ppidMeeseekFinalizado, glob->nMeeseekFinalizado, glob->iMeeseekFinalizado, tiempo);
            cerrarMemoria(&fd, glob);
        }
        strcat(mensaje, "Action executed: ");
        strcat(mensaje, tarea);
        strcat(mensaje, ", Dificulty: ");
        char *dif = malloc(sizeof(char) * 15);
        sprintf(dif, "%f", dificultad);
        strcat(mensaje, dif);
        free(dif);
        strcat(mensaje, ", Time of execution: ");
        strcat(mensaje, tiempo);
        free(tiempo);
        strcat(mensaje, "\n");
        return mensaje; // La salida formateada para la bitacora
    }
}


/*
Executes the program with arguments
@param: program for execute
@return: message for the record
*/
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
            //en caso de que falle el fork()
            printf("Existence is pain!!!");
            exit(0);
        }
        else
        {
            // Meeseeks Box
            wait(&pid);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f", tiempo_op);
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


/*
Complete the request of doing a math operation
@param: algebraic expression
@return: message for the record
*/
char *hacerLaMate(char *exp)
{
    clock_t inicio_op = clock();
    double tiempo_op;

    int fd[2];
    generatePipe(fd);
    pid_t pid = fork();
    if (pid == 0)
    {
        double resultado = hacerCalculos(exp);
        char *resulSTR = malloc(sizeof(char) * 30);
        sprintf(resulSTR, "%f", resultado);
        writeToPipe(fd, resulSTR); // Agregar el mensaje a la bitacora
        exit(0);
    }
    else
    {
        char *mensaje = malloc(sizeof(char) * 512), *recibido = malloc(sizeof(char) * 30), *tiempo = malloc(sizeof(char) * 30);

        if (pid < 0)
        {
            // en caso de que falle el fork()
            printf("Existence is pain!!!");
            exit(0);
        }
        else
        {
            // Meeseeks Box
            wait(&pid);
            tiempo_op = (double)(clock() - inicio_op) / CLOCKS_PER_SEC;
            sprintf(tiempo, "%f", tiempo_op);
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