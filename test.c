#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int generarDificultad(int min, int max) {
    srand(time(0));
    return (rand() % (max - min)) + min;
}

int main(int argc, char const *argv[])
{
    int a = execlp("ls","-la",".", NULL);

    printf("%d", a);
    return 0;
}
