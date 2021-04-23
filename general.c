#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tinyexpr.h"


#define MAX_STRING_LENGTH 256

/*
Prints the distinguish greeting of Mr.Meeseeks, his pid, ppid, level and instance numer
@param: level, instance number of Meeseek.
@return: void
*/
void sayHiMrMeeseeks(int nivel, int nInstancia){
    printf("Hi I'm Mr. Meeseeks! Look at Meeee. (pid: %d, ppid: %d, N: %d, i: %d)\n",
            getpid(),
            getppid(),
            nivel,
            nInstancia);
}

/*
Ask the user for his request to Mr.Meeseeks
@param: void
@return: The request made
*/
char* leerConsulta() {
    char* consulta = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("Make your request:  ");
    scanf(" %[^\n]s", consulta); //Reads a string until user inputs a new line character, considering the white spaces also as string.
    printf("\nOhhhh yeeaaah can do!!!\n");
    return consulta;
}

/*
Generate a random int between a range of numbers
@param: min value of the range, max value of the range
@return: Random int generated
*/
int generarDificultad(int min, int max) {
    srand(time(0)); //Sets a seed based in computer time to get different numbers every time.
    return (rand() % (max - min)) + min;
}

/*
Read the input difficulty of the user or randomly generate if unknown.
@param: void
@return: Difficulty of the request
*/
int leerDificultad() {
    int dificultad;
    printf("Which is your request difficuty? (100 = easy breezy, 0 = impossible, -1 = I don't know yet ");
    scanf(" %d", &dificultad);
    if(dificultad == -1){
        dificultad = generarDificultad(0, 100);
    }
    printf("Mr. Meeseeks realizara la tarea con dificultad %d\n ", dificultad);
    return dificultad;
}

/*
Calculate the duration of a request randomly (from 0.5s to 5s)
@param: void
@return: Duration of a request
*/
float calcularDuracion() {
    return ((float)generarDificultad(5, 50)) / 10;
}


int cantMrMeeseeks(){
    return 0;
}



/*
Calculate the duration of a request randomly (from 0.5s to 5s)
@param: void
@return: Duration of a request
*/
double eval(char* exp) {
    
    return te_interp(exp, 0);
}

int run(char* programName, char* arg1, char* arg2) {
    return execlp(programName, programName, arg1, arg2, NULL);
}