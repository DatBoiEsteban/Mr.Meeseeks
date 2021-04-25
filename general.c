#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tinyexpr.h"
#include <math.h>

#define MAX_STRING_LENGTH 256

/*
Prints the distinguish greeting of Mr.Meeseeks, his pid, ppid, level and instance numer
@param: level, instance number of Meeseek.
@return: void
*/
void sayHiMrMeeseeks(int nivel, int nInstancia)
{
    fprintf(stdout, "Hi I'm Mr. Meeseeks! Look at Meeee. (pid: %d, ppid: %d, N: %d, i: %d)\n",
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
char *leerConsulta()
{
    char *consulta = malloc(MAX_STRING_LENGTH * sizeof(char));
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
int generarRandom(int min, int max)
{
    srand(time(0)); //Sets a seed based in computer time to get different numbers every time.
    if (min == max)
    {
        return min;
    }
    return (rand() % (max - min)) + min;
}

/*
Read the input difficulty of the user or randomly generate if unknown
@param: void
@return: Difficulty of the request
*/
int leerDificultad()
{
    int dificultad;
    printf("Which is your request difficuty? (100 = easy breezy, 0 = impossible, -1 = I don't know yet) ");
    scanf(" %d", &dificultad);
    if (dificultad == -1)
    {
        dificultad = generarRandom(0, 100);
    }
    printf("Mr.Meeseeks will do the request with difficulty of: %d\n", dificultad);
    return dificultad;
}

/*
Solve the arithmetic operation.
@param:  The arithmetic expression
@return: Result of the calculation
*/
double hacerCalculos(char *exp)
{

    return te_interp(exp, 0);
}

/*
Execute a program.
@param: The name of the program and it's arguments.
@return: An int regarding if it execute the program successfully(0) or not
*/
int run(char *program)
{
    return system(program);
}

char *readProgram()
{
    char *programa = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("What is the program you want to run? ");
    scanf(" %[^\n]s", programa);
    return programa;
}


double probabilidadCompletarTarea(double dificultad, int cantHijos)
{
    return dificultad * (cantHijos / 150);
}

/*
*/
double diluirDificultad(double dificultad, int cantHijos)
{
    if (dificultad == 0)
    {
        return dificultad;
    }
    else
    {
        return dificultad + sqrt(cantHijos) ;
    }
}

/*
Calculates the amount of Mr.Meeseeks that will be needed to complete the request
*/
int cantMrMeeseeks(double dificultad)
{

    if ((dificultad >= 0) && (dificultad <= 45))
    {
        return generarRandom(3, 30);
    }
    else if ((dificultad > 45) && (dificultad <= 85))
    {
        return generarRandom(1, 2);
    }
    else
    {
        return 1;
    }
}

/*
Evaluates the probability of asking for help after trying the request
@param: The dificulty
@return:  
*/
int intentarTarea(double dificultad, int cantHijos)
{

    int tiempoTarea = generarRandom(1, 5); //Virtualize the execution time of the request

    sleep(tiempoTarea); //Mr.Meeseek is performing the request

    if (dificultad >= 86)
    {
        return 0; //The request is easy, no help will be needed
    }
    else
    {

        double probCompletado = probabilidadCompletarTarea(dificultad, cantHijos);
        if (probCompletado > 85.01)
        {
            return 0;
        }
        else
        {
            return cantMrMeeseeks(dificultad); //Mr.Meeseeks needs help
        }
    }
}
