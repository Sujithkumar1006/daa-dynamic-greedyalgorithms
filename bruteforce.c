#include <stdio.h>
#include <stdlib.h>
#include "create_knapsack.h"

#define ITEM_MAX 10
#define OUTPUT_FILE_NAME "output1.txt"

int calculate_count(int num)
{
    int items = 0;
    while (num)
    {
        items += num & 1;
        num >>= 1;
    }
    return items;
}

void bruteforce(const char *input, const char *output)
{
    FILE *input_file = fopen(input, "r");
    if (input_file == NULL)
    {
        perror("Error opening input file");
        return;
    }
    int no_of_items, total_capcity;
    fscanf(input_file, "%d %d", &no_of_items, &total_capcity);
    char items[ITEM_MAX][20];
    int profit[ITEM_MAX];
    int weight[ITEM_MAX];
    for (int index = 0; index < no_of_items; index++)
    {
        fscanf(input_file, "%s %d %d", items[index], &profit[index], &weight[index]);
    }
    fclose(input_file);
    int max_profit = 0;
    int max_weight = 0;
    int max = 0;
    for (int set = 0; set < (1 << no_of_items); set++)
    {
        int curr_profit = 0;
        int curr_weight = 0;
        for (int index = 0; index < no_of_items; index++)
        {
            if (set & (1 << index))
            {
                curr_profit += profit[index];
                curr_weight += weight[index];
            }
        }
        if (curr_weight <= total_capcity && curr_profit > max_profit)
        {
            max_profit = curr_profit;
            max_weight = curr_weight;
            max = set;
        }
    }
    FILE *opfile = fopen(output, "w");
    fprintf(opfile, "%d %d %d\n", calculate_count(max), max_profit, max_weight);
    for (int index = 0; index < no_of_items; index++)
    {
        if (max & (1 << index))
        {
            fprintf(opfile, "%s %d %d\n", items[index], profit[index], weight[index]);
        }
    }
    fclose(opfile);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of the program is createkn01 <file-name>.txt");
        return 0;
    }
    remove(OUTPUT_FILE_NAME);
    bruteforce(argv[1], OUTPUT_FILE_NAME);
    return 0;
}