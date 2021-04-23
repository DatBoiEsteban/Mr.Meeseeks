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
int generarRandom(int min, int max) {
    srand(time(0)); //Sets a seed based in computer time to get different numbers every time.
    return (rand() % (max - min)) + min;
}

/*
Read the input difficulty of the user or randomly generate if unknown
@param: void
@return: Difficulty of the request
*/
int leerDificultad() {
    int dificultad;
    printf("Which is your request difficuty? (100 = easy breezy, 0 = impossible, -1 = I don't know yet ");
    scanf(" %d", &dificultad);
    if(dificultad == -1){
        dificultad = generarRandom(0, 100);
    }
    printf("Mr.Meeseeks will do the request with difficulty of: %d\n ", dificultad);
    return dificultad;
}

/*
Calculates the amount of Mr.Meeseeks that will be needed to complete the request

*/
int cantMrMeeseeks(int dificultad){

    return 0;
}



/*
Solve the arithmetic operation.
@param:  The arithmetic expression
@return: Result of the calculation
*/
double hacerCalculos(char* exp) {

    return te_interp(exp, 0);
}

/*
Execute a program.
@param: The name of the program and it's arguments.
@return: An int regarding if it execute the program successfully(0) or not
*/
int run(char* programName, char* arg1, char* arg2) {
    return execlp(programName, programName, arg1, arg2, NULL);
}


/*
Evaluates the probability of asking for help after trying the request
@param: The dificulty
@return:  
*/
int pedirAyuda(int dificultad){
    
    //float tiempoTarea = generarRandom(1,5); //Para dormir entre 1s y 5s

    //El Mr. Meeseeks 'intenta' la tarea por un tiempo
    // sleep(segundos); 

    if(dificultad >= 85.01){
        return 0; //The request is easy, no help will be needed
    } 
    else{
        return 0; //Mr.Meeseeks needs help
    }
}

double calcularDuracion() {
    return 0;
}

char* readProgram() {
    char* programa = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("What is the program you want to run? ");
    scanf(" %[^\n]s", programa);
    return programa;
}

char* readArg() {
    char* arg = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("Insert argument: ");
    scanf(" %[^\n]s", arg);
    return arg;
}