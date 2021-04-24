#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "general.c"


int main(int argc, char const *argv[])
{
    int cantHijos = 1;
    double dificultad = 1;
    int interaciones = 0;
    int tareaCompleta = 1;

    printf("Si funciona\n");
    tareaCompleta = intentarTarea(dificultad, cantHijos);
    
    while(tareaCompleta != 0){
        cantHijos += tareaCompleta;

        dificultad = diluirDificultad(dificultad, cantHijos);

        interaciones++;
        
        tareaCompleta = intentarTarea(dificultad, cantHijos);
        printf("CantHijos: %d, Dificultad: %f, iteraciones: %d\n",cantHijos, dificultad, interaciones);
        
    }
    printf("CantHijos: %d, Dificultad: %f, iteraciones: %d\n",cantHijos, dificultad, interaciones);
    return 0; 
}
