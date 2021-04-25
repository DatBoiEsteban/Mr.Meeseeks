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
@return: the request made
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
@return: random int generated
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
@return: difficulty of the request
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
@param:  the arithmetic expression
@return: result of the calculation
*/
double hacerCalculos(char *exp)
{
    return te_interp(exp, 0);
}

/*
Execute a program.
@param: the name of the program and it's arguments.
@return: an int regarding if it execute the program successfully(0) or not
*/
int run(char *program)
{
    return system(program);
}

/*
Read the program
@param: void
@return: the program for execution
*/
char *readProgram()
{
    char *programa = malloc(MAX_STRING_LENGTH * sizeof(char));
    printf("What is the program you want to run? ");
    scanf(" %[^\n]s", programa);
    return programa;
}

/*
Evaluates the probabality of complete a request.
@param: difficculty of the request, amount of Meeseeks
@return: probabilty of succceding
*/
double probabilidadCompletarTarea(double dificultad, int cantHijos)
{
    return dificultad * (cantHijos / 150);
}

/*
Ages the request that are to hard of complete
@param: difficculty of the request, amount of Meeseeks
@return: the new difficulty of the request
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
Calculates the amount of Mr.Meeseeks for helping complete the request
@param: difficulty of the request
@return: amount of Meeseeks
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
Tries to complete the task
@param: The dificulty, amount of Meeseeks
@return:  0 if task complete or amount of Meeseek that are needed for more chance of completing the request.
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
