#include <stdio.h>
#include <unistd.h>

//#include "general.c"
//#include "globales.c"
#include "meeseeks_fork.c"

int main()
{
    int tipo = 0;
    int tipoTarea = 0;
    char *tarea = "";
    double dificultad = 0;
    int Box = getpid();
    char *bitacora = malloc( 10000);

    printf("Box pid: %d\n", Box);

    while (tipoTarea != 4)
    {

        printf("Desea trabajar con Threads? (0 = Threads 1 = Procesos) : ");
        scanf("%d", &tipo);
        printf("Seleccion el tipo de tarea que desea: \n    1. Accion Textual \n    2. Operación Textual  \n    3. Ejecutar Programa  \n    4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &tipoTarea);

        switch (tipoTarea)
        {
        case 1:
        {
            tarea = leerConsulta();
            dificultad = leerDificultad();

            if (tipo)
            {
                strcat(bitacora, realizarTarea(tarea, dificultad));
            }
            else
            {
            }
            break;
        }

        case 2:
        {
            tarea = leerConsulta();
            if (tipo == 1)
            {

                strcat(bitacora, hacerLaMate(tarea));
            }
            else
            {
            }
            break;
        }

        case 3:
        {
            char *programa = readProgram();
            if (tipo)
            {
                strcat(bitacora, ejecutarPrograma(programa));
            }
            else
            {
            }
            break;
        }

        case 4:
            printf("%s\n",bitacora);
            break;
        default:
            printf("\nLa opción %d no existe\n\n", tipoTarea);
            break;
        }

        // agregar a bitacora
    }
    return 0;
}