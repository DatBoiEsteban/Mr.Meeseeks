#include <stdio.h>
#include <unistd.h>
#include "meeseeks_fork.c"

int main()
{
    int tipo = 0;
    int tipoTarea = 0;
    double dificultad = 0;
    int Box = getpid();
    char *bitacora = malloc( 10000);

    printf("Box pid: %d\n", Box);

    while (tipoTarea != 4)
    {

        printf("What do you want to use? (0 = Threads(comming soon) 1 = Processes) : ");
        scanf("%d", &tipo);
        printf("Select the type of request: \n    1. Textual Request \n    2. Maths  \n    3. Execcute a program  \n    4. Exit\n");
        printf("Input your choice: ");
        scanf("%d", &tipoTarea);

        switch (tipoTarea)
        {
        case 1: 
        {
            char* tarea = leerConsulta();
            dificultad = leerDificultad();

            if (tipo)
            {
                char* res = realizarTarea(tarea, dificultad);
                strcat(bitacora, res);
            }
            else
            {
            }

            break;
        }

        case 2:
        {
            char* tarea = leerConsulta();
            if (tipo == 1)
            {
                char* res = hacerLaMate(tarea);
                strcat(bitacora, res);
            }
            else
            {
            }

            break;
        }

        case 3:
        {
            char* programa = readProgram();
            if (tipo)
            {
                char* res = ejecutarPrograma(programa);
                strcat(bitacora, res);
            }
            else
            {
            }
            break;
        }
        
        case 4:
            printf("%s\n",bitacora);
            free(bitacora);
            break;
        default:
            printf("\nThe option %d is invalid\n\n", tipoTarea);
            break;
        }
    }
    return 0;
}