#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "create_knapsack.h"

void create_knapsack(const char *file_name)
{
    srand(time(NULL));
    int n_value = rand() % 6 + 5;
    int list_items[n_value][2];
    FILE *file = fopen(file_name, "w");
    int total_weight = 0;
    for (int index = 0; index < n_value; index++)
    {
        int profit = rand() % 21 + 10;
        int weight = rand() % 16 + 5;
        list_items[index][0] = profit;
        list_items[index][1] = weight;
        total_weight += weight;
    }
    int total_capacity = (int)(0.6 * total_weight);
    fprintf(file, "%d %d\n", n_value, total_capacity);
    for (int index = 0; index < n_value; index++)
    {
        fprintf(file, "Item%d %d %d\n", index, list_items[index][0], list_items[index][1]);
    }
    fclose(file);
}