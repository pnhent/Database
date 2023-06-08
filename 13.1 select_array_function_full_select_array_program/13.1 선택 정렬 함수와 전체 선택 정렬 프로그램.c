//이름 : 박노현
//학과 : 컴퓨터공학과
//학번 : 202010553
//문제 : 전체 정렬 프로그램(선택, 삽입, 버블, 셸, 병합, 퀵정렬)
//실습일 : 20230608

#include <stdio.h>
#include <stdlib.h>
#define SWAP(x, y, t) ((t)=(x),(x)=(y),(y)=(t))
#define MAX_SIZE 1024


void printArray(int arr[], int n, char *str) //13.1 선택 정렬 함수와 전체 선택 정렬 프로그램

{
    int i;
    printf("%s = ", str);
    for (i=0; i<n; i++) printf("%3d", arr[i]); 
    printf("\n");
}

void printStep(int arr[], int n, int val) //13.1 선택 정렬 함수와 전체 선택 정렬 프로그램

{
    int i;
    printf(" Step %2d = ", val);
    for(i=0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void selection_sort(int list[], int n) //13.1 선택 정렬 함수와 전체 선택 정렬 프로그램
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

void insertion_sort(int list[], int n) //13.2 삽입 정렬 함수
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

void bubble_sort(int list[], int n) //13.3 버블 정렬 함수
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

void insertion_sort_fn(int list[], int n, int(*f)(int, int)) //13.4 함수 포인터를 매개 변수로 받는 삽입 정렬 함수
{
    int i, j, key;
    for(i=1; i<n; i++)
    {
        key = list[i];
        for(j=i-1; j>0 && f(list[j],key) < 0; j--)
            list[j+1] = key;
            printStep(list, n, i);
    }
}

static void sortGapInsertion(int list[], int first, int last, int gap) //13.5 쉘 정렬 함수-1
{
    int i, j, key;
    for(i=first+gap; i<=last; i=i+gap)
    {
        key = list[i];
        for(j=i-gap; j>=first && key<list[j]; j=j-gap)
            list[j+gap]=list[j];
        list[j+gap]=key;
    }
}

void shell_sort(int list[], int n) //13.5 쉘 정렬 함수-2
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

static void merge(int list[], int left, int mid, int right) //13.6 병합 정렬 함수-1
{
    int i, j, k = left, l;
    static int sorted[MAX_SIZE];
    for(i=left, j=mid+1; i<=mid && j<=right;)
        sorted[k++] = (list[i]<=list[j]) ? list[i++] : list[j++];
    
    if(i > mid)
        for(l=j; l<=right; l++, k++)
            sorted[k] = list[l];
    else
        for(l=i; l<=mid; l++, k++)
            sorted[k] = list[l];
    for(l=left; l<=right; l++)
        list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right) //13.6 병합 정렬 함수-2
{
    if(left<right)
    {
        int mid = (left+right)/2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
    }
}

int partition(int list[], int left, int right) //13.8 퀵 정렬에서 partition() 함수
{
    int pivot, tmp;
    int low, high;

    low = left;
    high = right+1;
    pivot = list[left];
    do
    {
        do
        {
            low++;
        } while (low <= right && list[low] < pivot);
        do
        {
            high--;
        } while (high >= left && list[high] > pivot);
        if(low<high) SWAP(list[low], list[high], tmp);
    } while (low<high);

    SWAP(list[left], list[high], tmp);
    return high;
}

void quick_sort(int list[], int left, int right) //13.7 퀵 정렬 함수
{
    int q;
    if(left<right)
    {
        q = partition(list,left,right);
        quick_sort(list,left,q-1);
        quick_sort(list,q+1,right);
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

    for(i=0; i<9; i++)
    list[i] = dcopy[i];
    merge_sort(list, 0, 8);
    printArray(list, 9, "mergesort");

    for(i=0; i<9; i++)
    list[i] = dcopy[i];
    quick_sort(list, 0, 8);
    printArray(list, 9, "quicksort");

    return 0;
}