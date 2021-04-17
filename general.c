#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tinyexpr.h"


#define MAX_STRING_LENGTH 256

char* leerConsulta() {
    char *consulta = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("Hi I'm Mr. Meeseeks, Look at Meee.  ");
    scanf(" %[^\n]s", consulta); 
    return consulta;
}

int generarDificultad(int min, int max) {
    srand(time(0));
    return (rand() % (max - min)) + min;
}

int leerDificultad() {
    int dificultad;
    printf("Conoce la dificultad de la solicitud? (100 = facil, 0 = imposible, -1 = desconoce dificultad): ");
    scanf(" %d", &dificultad);
    if(dificultad == -1){
        dificultad = generarDificultad(0, 100);
    }
    printf("Mr. Meeseeks realizara la tarea con dificultad %d\n ", dificultad);
    return dificultad;
}

float calcularDuracion() {
    return ((float)generarDificultad(5, 50)) / 10;
}

double eval(char* exp) {
    return te_interp(exp, 0);
}

