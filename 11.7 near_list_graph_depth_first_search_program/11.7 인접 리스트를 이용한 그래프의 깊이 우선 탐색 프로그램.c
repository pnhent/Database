//이름 : 박노현
//학번 : 202010553
//학과 : 컴퓨터공학과
//문제 : 11.7 인접 리스트를 이용한 그래프의 깊이 우선 탐색 프로그램
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

void print_graph(char* msg)
{
    int i;
    GNode* v;
    printf("%s%d\n", msg, vsize);
    for(i=0; i<vsize; i++)
    {
        printf("%c ", vdata[i]);

        for(v=adj[i]; v != NULL; v=v->link)
            printf(" %c", vdata[v->id]);
        printf("\n");
    }
}

void load_graph(char *filename)
{
    int i, j, val, n;
    char str[80];
    FILE *fp = fopen(filename, "r");
    if(fp != NULL)
    {
        init_graph();
        fscanf(fp, "%d", &n);
        for(i=0; i<n; i++)
        {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for(j=0; j<n; j++)
            {
                fscanf(fp, "%d", &val);
                if(val != 0)
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
    for( i=0; i<vsize; i++)
        visited[i] = 0;
}

void DFS(int v)
{
    GNode *p;
    visited[v] = 1;
    printf("%c", vdata[v]);
    for(p=adj[v]; p!=NULL; p=p->link)
        if(visited[p->id] == 0);
            DFS(p->id);
}

int main(void)
{
    load_graph("C:\\Users\\pa010\\Documents\\DATABASE\\11.6 near hangyeol graph depth search program\\graph.txt");
    reset_visited();
    printf("DFS ==> ");
    DFS( 0 );
    printf("\n");

    return 0;
}