#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int countmax(int num)
{
    int count = 0;
    while (num)
    {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

// function to solve knapsack using improved greedy algorithm
void improvedgreedy(const char *fileitems, const char *opFileitems)
{
    FILE *ipfile = fopen(fileitems, "r");
    FILE *opFile = fopen(opFileitems, "w");
    int no_of_items, capacity;
    fscanf(ipfile, "%d %d", &no_of_items, &capacity);
    char items[no_of_items][20];
    int profit[no_of_items];
    int weight[no_of_items];
    for (int index = 0; index < no_of_items; index++)
    {
        fscanf(ipfile, "%s %d %d", items[index], &profit[index], &weight[index]);
    }
    fclose(ipfile);
    for (int index = 0; index < no_of_items - 1; index++)
    {
        for (int inner_index = index + 1; inner_index < no_of_items; ++inner_index)
        {
            double vi1 = (double)profit[index] / weight[index];
            double vi2 = (double)profit[inner_index] / weight[inner_index];
            if (vi1 < vi2)
            {
                int temp_profit = profit[index];
                int temp_weight = weight[index];
                char temp_item[20];
                strcpy(temp_item, items[index]);
                strcpy(items[index], items[inner_index]);
                profit[index] = profit[inner_index];
                weight[index] = weight[inner_index];
                strcpy(items[inner_index], temp_item);
                profit[inner_index] = temp_profit;
                weight[inner_index] = temp_weight;
            }
        }
    }
    int total_profit = 0;
    int total_weight = 0;
    int maxset[no_of_items];
    memset(maxset, 0, no_of_items * sizeof(int));
    for (int index = 0; index < no_of_items; index++)
    {
        if (total_weight + weight[index] <= capacity)
        {
            total_weight += weight[index];
            total_profit += profit[index];
            maxset[index] = 1;
        }
    }
    int maxitem = 0;
    for (int index = 0; index < no_of_items; index++)
    {
        if (maxset[index])
        {
            maxitem++;
        }
    }
    fprintf(opFile, "%d %d %d\n", maxitem, total_profit, total_weight);
    for (int index = 0; index < no_of_items; index++)
    {
        if (maxset[index])
        {
            fprintf(opFile, "%s %d %d\n", items[index], profit[index], weight[index]);
        }
    }
    fclose(opFile);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage of the program is igreedy <file-name>.txt");
        return 0;
    }
    srand((unsigned int)time(NULL));
    improvedgreedy(argv[1], "output3.txt");
    return 0;
}
