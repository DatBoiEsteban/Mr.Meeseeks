#include <stdio.h>
#include <unistd.h>

#include "general.c"

int main(){
    int tipo;
    int tipoTarea;
    char* tarea;
    double dificultad;
    int Box = getpid();

    printf("Box pid: %d\n\n\n", Box);

    while(tipoTarea != 4) {

        printf("Desea trabajar con Threads? (1 = Threads 0 = Procesos) : ");
        scanf("%d", &tipo);

        printf("Seleccion el tipo de tarea que desea: \n    1. Accion Textual \n    2. Operación Textual  \n    3. Ejecutar Programa  \n    4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &tipoTarea);

        switch(tipoTarea) {
            case 1: {
                char* consulta = leerConsulta();
                int dificultad = leerDificultad();
                float duracion = calcularDuracion();
                if(tipo){
                    
                } else {

                }
                break;
            }
                
            case 2: {
                if(tipo){

                } else {
                    
                }
                break;
            }
                
            case 3: {
                if(tipo){

                } else {
                    
                }
                break;
            }
                
            case 4:
                break;
            default:
                printf("\nLa opción %d no existe\n\n", tipoTarea);
                break;
        }
    }
    return 0;
}