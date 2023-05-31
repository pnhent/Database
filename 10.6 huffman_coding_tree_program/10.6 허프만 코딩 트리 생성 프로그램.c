//이름 : 박노현
//학번 : 202010553
//학과 : 컴퓨터공학과
//문제 : 10.6 허프만 코딩 트리 생성 프로그램
//실습일 : 20230518

#include <stdio.h>
#include <stdlib.h>
#define MAX_HEAP_NODE 200

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

typedef int HNode;
#define Key(n)   (n)

HNode heap[MAX_HEAP_NODE];
int heap_size;

#define Parent(i) (heap[i/2])
#define Left(i) (heap[i*2])
#define Right(i) (heap[i*2+1])

void init_heap()
{
    heap_size = 0;
}

int is_empty_heap()
{
    return heap_size == 0;
}

int is_full_heap()
{
    return (heap_size == MAX_HEAP_NODE -1);
}

HNode find_heap() 
{
    return heap[1];
}

void insert_heap(HNode n)
{
    int i;
    if(is_full_heap()) return;
    i = ++(heap_size);
    while (i != 1 && Key(n) < Key(Parent(i)))
    {
        heap[i] = Parent(i);
        i /= 2;
    }
    heap[i] = n;
}

HNode delete_heap()
{
    HNode hroot, last;
    int parent = 1, child = 2;

    if(is_empty_heap() )
        error("힙 트리 공백 에러");
    
    hroot = heap[1];
    last = heap[heap_size--];
    while(child <= heap_size)
    {
        if(child<heap_size && Key(Left(parent))>Key(Right(parent)))
            child++;
        if(Key(last) <= Key(heap[child]))
            break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;
    return hroot;
}

void make_tree(int freq[], int n)
{
    HNode e1, e2;
    int i;

    init_heap();
    for(i=0; i<n; i++)
        insert_heap(freq[i]);
    
    for(i=1; i<n; i++)
    {
        e1 = delete_heap();
        e2 = delete_heap();
        insert_heap(Key(e1) + Key(e2));
        printf(" (%d+%d)\n", Key(e1), Key(e2));
    }
}

int main(void)
{
    char label[] = { 'A', 'B', 'C', 'D', 'E' };
    int freq[] = { 15, 12, 8, 6, 4 };
    make_tree(freq, 5);
}