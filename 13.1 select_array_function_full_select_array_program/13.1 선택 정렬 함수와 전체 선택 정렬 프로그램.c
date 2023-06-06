#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_SIZE


void printArray(int arr[], int n, char *str)
{
    int i;
    printf("%s = ", str);
    for (i=0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void printStep(int arr[], int n, int val)
{
    int i;
    printf(" Step %2d = ", val);
    for(i=0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void selection_sort(int list[], int n)
{
    int i, j, least, tmp;
    for(i=0; i<n-1; i++)
    {
        least = i;
        for(j=i+1; j<n; j++)
            if(list[j]<list[least]) least = j;
        SWAP(list[i], list[least],tmp);
        printStep(list, n, i+1);
    }
}

void insertion_sort(int list[], int n)
{
    int i, j, key;
    for(i=1; i<n; i++)
    {
        key = list[i];
        for(j=i-1; j>=0 && list[j] > key; j--)
            list[j+1] = list[j];
        list[j+1] = key;
        printStep(list, n, i);
    }
}

void bubble_sort(int list[], int n)
{
    int i, j, bChanged, tmp;
    for(i=n-1; i>0; i--)
    {
        bChanged = 0;
        for(j=0; j<i; j++)
            if(list[j]>list[j + 1])
            {
                SWAP(list[j],list[j+1], tmp);
                bChanged = 1;
            }
        if(!bChanged) break;
        printStep(list, n, n-i);
    }
}

void insertion_sort_fn(int list[], int n, int(*f)(int, int))
{
    int i, j, key;
    for(i=1; i<n; i++)
    {
        key = list[i];
        for(j=i-1; j>0 && f(list[j],key) < 0; j--)
            list[j+1] = key;
            printStep(lst, n, i);
    }
}

static void sortGapInsertion(int list[], int first, int last, int gap)
{
    int i, j, key;
    for(i=frist+gap; i<=last; i=i+gap)
    {
        key = list[i];
        for(j=i-gap; j>=first && key<list[j]; j=j-gap)
            list[j+gap]=list[j];
        list[j+gap]=key;
    }
}

void shell_sort(int list[], int n)
{
    int i, gap, count=0;
    for(gap=n/2; gap>0; gap = gap/2)
    {
        if((gap%2) == 0) gap++;
        for(i=0; i<gap; i++)
            sortGapInsertion(list, i, n-1, gap);
        printStep(list, n, ++count);
    }
}


int main(void)
{
    int i, list[9] = {5, 3, 8, 4, 9, 1, 6, 2, 7}, dcopy[9];
    printArray(list, 9, "Original ");

    for(i=0; i<9; i++)
        dcopy[i] = list[i];

    selection_sort(list, 9);
    printArray(list, 9, "Selection");

    for(i=0; i<9; i++)
        list[i] = dcopy[i];
    insertion_sort(list, 9);
    printArray(list, 9, "insertion");

    for(i=0; i<9; i++)
        list[i] = dcopy[i];
    bubble_sort(list, 9);
    printArray(list, 9, "bubblesort");

    return 0;
}