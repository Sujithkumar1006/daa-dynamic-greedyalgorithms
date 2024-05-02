#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "create_knapsack.h"


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of the program is createkn01 <file-name>.txt");
        return 0;
    }
   
    create_knapsack(argv[1]);
    return 0;
}