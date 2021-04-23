#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generarDificultad(int min, int max) {
    srand(time(0));
    return (rand() % (max - min)) + min;
}

int main(int argc, char const *argv[])
{
    int rand = generarDificultad(0, 100);
    printf("%d",rand);
    return 0;
}
