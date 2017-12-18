// A C Program to demonstrate adjacency list representation of graphs
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

typedef int Status;
typedef int QElemtype;
typedef int boolean;

boolean* visited = 0;

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head; // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjancency lists.
struct Graph
{
    int V; // Size of array will be V(number of vertices in graph)
    struct AdjList *array;
};

// A function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A function to create a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size of array will be V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making a head node
    int i;
    for(i = 0; i < V; ++i)
        {
            graph->array[i].head = (AdjListNode *)malloc(sizeof(AdjListNode));
            graph->array[i].head->next = NULL;
            graph->array[i].head->dest = i;
        }
    return graph;
}

// Add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest. A new node is added to the adjacency
    struct AdjListNode* newNode = newAdjListNode(dest);

    // The node is added at the beginning
    newNode->next = graph->array[src].head->next;
    graph->array[src].head->next = newNode;

    // Since the graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head->next;
    graph->array[dest].head->next = newNode;
}

// Delete an edge from an undirected graph
void deleteEdge(struct Graph* graph, int src, int dest)
{
    // Delete an edge from src to dest
    struct AdjListNode* preNode = graph->array[src].head;
    struct AdjListNode* delNode = preNode->next;

    // Search for the location of deleted edge in the adjacency list
    while(delNode && delNode->dest != dest)
    {
        preNode = preNode->next;
        delNode = preNode->next;
    }
    if(!delNode) 
    {
        printf("Not Found!");
        return;
    }

    // perform the removal
    preNode->next = delNode->next;
    free(delNode);
    delNode = NULL;

    // Since the graph is undirected, delete an edge from dest to src also
    preNode = graph->array[dest].head;
    delNode = preNode->next;
    while(delNode && delNode->dest !=src)
    {
        preNode = preNode->next;
        delNode = preNode->next;
    }
    preNode->next = delNode->next;
    free(delNode);
    delNode = NULL;
}

// A function to print the adjacency list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for(v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* p = graph->array[v].head->next;
        printf("\n Adjacency list of vertex %d\n head", v);
        while(p)
        {
            printf(" -> %d", p->dest);
            p = p->next;
        }
        printf("\n");
    }
}

void DFS(struct Graph* graph, int v)
{
    AdjListNode* w = 0;

    // mark the current node as visited and print it
    visited[v] = TRUE;  
    printf(" Vertex%d  ", v);

    // recur for all the vertices adjacent to the vertex
    for(w = graph->array[v].head; w != NULL; w = w->next)
        if(visited[w->dest] == FALSE) DFS(graph, w->dest);
}

// DFS traversal of the vertices reachable from v
// It uses recursive DFS()
void DFSTraverse(struct Graph* graph)
{
    // mark all the vertices as not visited
    int v;
    visited = (boolean *)malloc(graph->V * sizeof(boolean));    
    for(v = 0; v < graph->V; ++v)visited[v] = FALSE;

    // call the recursive helper function
    // and make sure all the vertices will be visited
    for(v = 0; v < graph->V; ++v)
        if(visited[v] == FALSE)DFS(graph, v);
}

// A linked list node to store a queue entry
typedef struct QNode
{
    QElemtype data;
    struct QNode* next;
}QNode, *QueuePtr;

// The queue
// front stores the front node of linked list
// rear stores the last node of linked list
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

// A function to create an empty queue
Status InitQueue(LinkQueue &Q)
{
    QNode *p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)return ERROR;
    p->next = NULL;
    Q.front = p;
    Q.rear = p;
    return OK;
}

// A function to add an element e to the queue
Status EnQueue(LinkQueue &Q, QElemtype e)
{
    // create a new node
    QNode *p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p)return ERROR;

    // add the new node at the end of queue and change rear
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

// A function to remove an element e from the queue
Status DeQueue(LinkQueue &Q, QElemtype &e)
{
    // if queue is empty, return ERROR
    if(Q.front == Q.rear)return ERROR;

    // store and move one node after front
    QNode *p;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;

    // if queue becomes empty, then change rear also as front
    if(p == Q.rear)Q.rear = Q.front;
    free(p);
    return OK; 
}

void BFSTraverse(Graph* graph)
{
    AdjListNode *w = 0;

    // create a queue for BFS
    LinkQueue Q;
    InitQueue(Q);

    // mark all the vertices as not visited
    int v, u;
    visited = (boolean *)malloc(graph->V * sizeof(boolean));
    for(v = 0; v < graph->V; ++v)visited[v] = FALSE;

    // make sure all the vertices will be visited
    for(v = 0; v < graph->V; ++v)
        if(visited[v] == FALSE)
        {
            visited[v] = TRUE;
            printf(" Vertex%d  ", v);
            EnQueue(Q, v);
            while(Q.front != Q.rear)
            {
                // DeQueue a vertex from queue and u get it
                DeQueue(Q, u);

                // get all adjacent vertices of the dequeued vertex u
                // if a adjacent has not visited, then mark it visited and enqueue it
                for(w = graph->array[u].head; w != NULL; w = w->next)
                    if(visited[w->dest] == FALSE)
                    {
                        visited[w->dest] = TRUE;
                        printf(" Vertex%d  ", w->dest);
                        EnQueue(Q, w->dest);
                    }
            }
        }
}

// Driver Program to test above functions
int main(void)
{
    // create the graph given
    int V = 5;
    struct Graph* graph = createGraph(V);
    // test addEdge();
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    // print the adjacency list representation of the above graph
    printGraph(graph);

    // test Traverse();
    printf("\n The result of traversal:\n");
    DFSTraverse(graph);
    // BFSTraverse(graph);
    printf("\n");

    // test deleteEdge();
    printf("\n After deleting:");
    deleteEdge(graph, 1, 4);
    deleteEdge(graph, 2, 3);
    // print the adjacency list representation of the above graph
    printGraph(graph);

    return 0;
}
