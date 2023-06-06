//이름 : 박노현
//학번 : 202010553
//학과 : 컴퓨터공학과
//문제 : 11.9 인접 리스트를 이용한 그래프의 너비 우선 탐색 프로그램
//실습일 : 20230525

#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS 256

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

typedef struct GraphNode
{
    int id;
    struct GraphNode* link;
} GNode;

typedef char VtxData;
GNode* adj[MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

int is_empty_graph()
{
    return(vsize == 0);
}

int is_full_graph()
{
    return(vsize >= MAX_VTXS);
}

void init_graph()
{
    int i;
    vsize=0;
    for(i=0; i<MAX_VTXS; i++)
        adj[i] = NULL;
}

void rest_graph()
{
    int i;
    GNode* n;
    for(i=0; i<vsize; i++)
    {
        while(adj[i] != NULL)
        {
            n = adj[i];
            adj[i] = n->link;
            free( n );
        }
    }
    vsize = 0;
}

void insert_vertex ( char name )
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

void insert_edge(int u, int v)
{
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->link = adj[u];
    n->id = v;
    adj[u] = n;
}

void load_graph( char *filename)
{
    int i, j, val, n;
    char str[80];
    FILE *fp = fopen(filename, "r");
    if( fp != NULL )
    {
        init_graph();
        fscanf(fp, "%d", &n);
        for(i=0 ; i<n ; i++)
        {
            fscanf(fp, "%s", str);
            insert_vertex( str[0] );
            for(j=0 ; j<n ; j++)
            {
                fscanf(fp, "%d", &val);
                if( val != 0 )
                    insert_edge(i, j);
            }
        }
        fclose(fp);
    }
}

int visited[MAX_VTXS];
void reset_visited()
{
    int i;
    for( i=0; i<vsize ; i++)
        visited[i] = 0;
}

#define MAX_QUE_SIZE 100  

typedef int Element;
Element data[MAX_QUE_SIZE];
int front;
int rear;

void init_que()          
{
    front = rear = 0;
}

int is_empty()            
{
    return front == rear;
}

int is_full()          
{
    return front == (rear + 1) % MAX_QUE_SIZE;
}

int size()             
{
    return(rear - front + MAX_QUE_SIZE) % MAX_QUE_SIZE;
}

void enqueue(Element val)
{
    if (is_full())
        error("que full error");
    rear = (rear + 1) % MAX_QUE_SIZE;
    data[rear] = val;
}

Element dequeue()
{
    if (is_empty())
        error("que empty error");
    front = (front + 1) % MAX_QUE_SIZE;
    return data[front];
}

Element peek()
{
    if (is_empty())
        error("que empty error");
    return data[(front + 1) % MAX_QUE_SIZE];
}

void BFS(int v)
{
    GNode *w;
    visited[v] = 1;

    printf("%c ", vdata[v]);
    init_que();
    enqueue(v);
    while(!is_empty())
    {
        v = dequeue();
        for(w=adj[v]; w!=NULL; w=w->link)
        {
            if(!visited[w->id])
            {
                visited[w->id] = 1;
                printf("%c ", vdata[w->id]);
                enqueue(w->id);
            }
        }
    }
}

int main(void)
{
    load_graph("C:\\Users\\pa010\\Documents\\DATABASE\\11.6 near hangyeol graph depth search program\\graph.txt");
    reset_visited();
    printf("BFS ==> ");
    BFS(0);
    printf("\n");

    return 0;
}