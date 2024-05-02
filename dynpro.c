#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM_MAX 10

int **create_entries_array(int no_of_items, int capacity)
{
    int **entries = malloc((no_of_items + 1) * sizeof(int *));
    for (int index = 0; index <= no_of_items; index++)
    {
        entries[index] = malloc((capacity + 1) * sizeof(int));
    }
    for (int index = 0; index <= no_of_items; index++)
    {
        for (int inner_index = 0; inner_index <= capacity; inner_index++)
        {
            entries[index][inner_index] = 0;
        }
    }
    return entries;
}

void free_allocated_entries(int no_of_items, int **entries)
{
    for (int index = 0; index <= no_of_items; index++)
    {
        free(entries[index]);
    }
    free(entries);
}

int RDynamicP(int no_of_items, int capacity, int *weight, int *profit, int **flag, int **entries)
{
    //  printf("Items %d and %d\n", no_of_items, capacity);

    if (no_of_items == 0 || capacity < 0)
    {
        return 0;
    }
    else
    {
        for (int i = no_of_items - 1; i >= 0; i--)
        {
        //    printf("Weightttt %d and %d \n", weight[i], capacity);
            if (weight[i] > capacity)
            {
                flag[no_of_items][capacity] = 1;
                return RDynamicP(no_of_items - 1, capacity, weight, profit, flag, entries);
            }
            else
            {

                int tmp1 = RDynamicP(no_of_items - 1, capacity, weight, profit, flag, entries);
                int tmp2 = profit[i] + RDynamicP(no_of_items - 1, capacity - weight[i], weight, profit, flag, entries);
                // printf("Temp1 is %d and temp2 is %d and n is %d and c is %d\n", tmp1, tmp2, no_of_items, capacity);
                if (tmp1 > tmp2)
                {
                    flag[no_of_items][capacity] = 0;
                    entries[no_of_items][capacity] = tmp1;
                    return tmp1;
                }
                else
                {
                    flag[no_of_items][capacity] = 1;
                    entries[no_of_items][capacity] = tmp2;
                    return tmp2;
                }
            }
        }
    }

    return 0;
}

void refined_dynamic_programming(char *input_file)
{
    FILE *ipfile = fopen(input_file, "r");
    FILE *output_file = fopen("entries2.txt", "w");
    if (ipfile == NULL)
    {
        perror("Error opening input file");
        return;
    }

    int no_of_items, capacity;
    fscanf(ipfile, "%d %d", &no_of_items, &capacity);
    if (no_of_items <= 0 || capacity <= 0)
    {
        return;
    }
    char items[ITEM_MAX][20];
    int profit[ITEM_MAX];
    int weight[ITEM_MAX];
    for (int index = 0; index < no_of_items; index++)
    {
        fscanf(ipfile, "%s %d %d", items[index], &profit[index], &weight[index]);
    }
    int **entries = create_entries_array(no_of_items, capacity);
    int **flag = create_entries_array(no_of_items, capacity);
    RDynamicP(no_of_items, capacity, weight, profit, flag, entries);
    int sb, sk;
    for (sb = 1; sb <= no_of_items; sb++)
    {
        fprintf(output_file, "row%d ", sb);
        for (sk = 0; sk <= capacity; sk++)
        {
            if (flag[sb][sk] != 0)
            {
                fprintf(output_file,"%6d ", entries[sb][sk]);
            }
        }
        fprintf(output_file,"\n");
    }
    fclose(output_file);
    free_allocated_entries(no_of_items, entries);
    free_allocated_entries(no_of_items, flag);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage of the program is dynpro <file-name>.txt");
        return 0;
    }
    refined_dynamic_programming(argv[1]);
    return 0;
}