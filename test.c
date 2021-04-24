#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "general.c"


int main(int argc, char const *argv[])
{
    int cantHijos = 1;
    float dificultad = 30.0;
    int interaciones = 0;
    int tareaCompleta = 1;

    printf("Si funciona");

    while(tareaCompleta != 0){
        
        int ayudaMeeseek = intentarTarea(dificultad, cantHijos);
      
        cantHijos += ayudaMeeseek;

        dificultad = diluirDificultad(dificultad, cantHijos);

        interaciones++;

        tareaCompleta = ayudaMeeseek;

        printf("CantHijos: %d, Dificultad: %f, iteraciones: %d",cantHijos, dificultad, interaciones);
    }
   return 0; 
}
