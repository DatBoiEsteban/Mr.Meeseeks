#include <stdio.h>
#include <unistd.h>

//#include "general.c"
//#include "globales.c"
#include "meeseeks_fork.c"

int main()
{
    int tipo;
    int tipoTarea;
    char *tarea;
    int dificultad;
    double duracion;
    int Box = getpid();
    globales glob;

    printf("Box pid: %d\n\n", Box);

    while (tipoTarea != 4)
    {

        printf("Desea trabajar con Threads? (0 = Threads 1 = Procesos) : ");
        scanf("%d", &tipo);
        init_sem(&glob, tipo);
        printf("Seleccion el tipo de tarea que desea: \n    1. Accion Textual \n    2. Operación Textual  \n    3. Ejecutar Programa  \n    4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &tipoTarea);

        switch (tipoTarea)
        {
        case 1:
        {
            tarea = leerConsulta();
            dificultad = leerDificultad();
            duracion = calcularDuracion();
            if (tipo)
            {
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
                char *as = hacerLaMate(tarea);
                printf(as);
            }
            else
            {
            }
            break;
        }

        case 3:
        {
            if (tipo)
            {
                int a = run("ls", "-la", "/home");
                printf("%d\n", a);
            }
            else
            {
            }
            break;
        }

        case 4:
            break;
        default:
            printf("\nLa opción %d no existe\n\n", tipoTarea);
            break;
        }

        // agregar a bitacora
    }
    return 0;
}