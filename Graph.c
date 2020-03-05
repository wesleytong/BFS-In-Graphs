/****************************************************************************************
*  Wesley Tong
*  PA4
*  wtong5
*  Graph.c
*  Implemetation file for Graph ADT
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

#define WHITE 1
#define GREY 2
#define BLACK 3

typedef struct GraphObj{
  List *adjacencyList;
  int *color;
  int *parent;
  int *distance;
  int order;
  int size;
  int source;
}GraphObj;

//Constructors/Destructors
//newGraph - Creates and returns a Graph with n vertices and no edges
Graph newGraph(int n){
  Graph G = malloc(sizeof(GraphObj));
  G->adjacencyList = malloc(sizeof(List)*(n+1));
  G->color = malloc(sizeof(int)*(n+1));
  G->parent = malloc(sizeof(int)*(n+1));
  G->distance = malloc(sizeof(int)*(n+1));
  G->order = n;
  G->size = 0;
  G->source = NIL;

  //need to also add loop to set the default settings
  for(int i = 0; i < n; i++){
    G->adjacencyList[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  return G;
}

//freeGraph - Frees all dynamic memory associated with Graph and sets *pG to NULL
void freeGraph(Graph* pG){
  //for()
  if(pG!=NULL && *pG!=NULL){
    for(int i = 0; i < ((*pG)->order+1); i++){
      freeList(&(*pG)->adjacencyList[i]);
    }
  }
  free((*pG)->adjacencyList);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);
  *pG = NULL;
}

//Access Functions
//getOrder - Returns order
int getOrder(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getOrder() on a NULL Graph");
    exit(1);
  }
  return G->order;
}

//getSize - Returns size
int getSize(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getOrder() on a NULL Graph");
    exit(1);
  }
  return G->size;
}

//getSource - Returns the most recently used source vertex
int getSource(Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getOrder() on a NULL Graph");
    exit(1);
  }
  return G->source;
}

//int getParent(Graph G, int u) - Returns the parent of vertex u in the BFS Tree, or NIL if BFS has not yet been called. pre: 1 <= u <= getOrder(G)
int getParent(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getParent() on a NULL Graph");
    exit(1);
  }
  //failing test script with if(u >= 1 && u <= getOrder(G)) - use exit cond instead
  //still failing test script
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getParent() out of bounds");
    exit(1);
  }
  return G->parent[u];
}

//int getDist(Graph G, int u) - Returns the distance from the most recent BFS source to vertex U, or INF if BFS() has not been called. pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getDist() on a NULL Graph");
    exit(1);
  }
  //failing test script with if(u >= 1 && u <= getOrder(G))
  //now passing
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getDist() out of bounds");
    exit(1);
  }
  if(getSource(G) == NIL){
    return INF;
  }
  return G->distance[u];
}

//void getPath(List L, Graph G, int u) - Appends to List L the vertices of a shortest path in G from source to u, or appends to L NIL if no such path exists. pre: getSource(G) != NIL, BFS() must be called before getPath(). 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u){
  if(G==NULL){
    printf("Graph Error: Calling getPath() on a NULL Graph");
    exit(1);
  }
//  failing test script
/*
  if( u >= 1 && u <= getOrder(G)){
    if(u == G->source){
      prepend(L,u);
    }
    else if(G->parent[u] == NIL){
      append(L, NIL);
    }
    else{
      prepend(L,u);
      getPath(L, G, G->parent[u]);
    }
  }
  else{
    printf("Graph Error: Calling getPath() on invalid value of u");
    exit(1);
  }*/
  if(u < 1 || u > getOrder(G)){
    printf("Graph Error: Calling getPath() on invalid value of u");
    exit(1);
  }
  if(u == G->source){
    prepend(L,u);
  }
  else if(G->parent[u] == NIL){
    append(L, NIL);
  }
  else{
    prepend(L,u);
    getPath(L, G, G->parent[u]);
  }
}

//void makeNull(Graph G) - Deletes all edges of G, restoring to original no edge state (null graph).
void makeNull(Graph G){
  //if already Null - set source to NIL and size = 0
  G->size = 0;
  G->source = NIL;

  if(G!=NULL){
    for(int i=0; i<getOrder(G);i++){
      G->color[i] = WHITE;
      G->parent[i] = INF;
      G->distance[i] = NIL;
      clear(G->adjacencyList[i]);
    }
  }
}

//void addEdge(Graph G, int u, int v) - Inserts a new edge joining u to v (u is the adjacency list of v, and v to the adjacency list of u). pre: 1 <= u <= getOrder(G)
void addEdge(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: Calling addEdge() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
      printf("Graph Error: Graph Vertices is out of bounds");
      exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
}
//void addArc(Graph G, int u, int v) - Inserts a new directed edge from u to v. pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v){
  if(G==NULL){
    printf("Graph Error: Calling addEdge() on a NULL Graph");
    exit(1);
  }
  if( u < 1 || u > getOrder(G)){
    printf("Graph Error: Graph Vertices is out of bounds");
    exit(1);
  }
  if( v < 1 || v > getOrder(G)){
    printf("Graph Error: Graph Vertices is out of bounds");
    exit(1);
  }
  moveFront(G->adjacencyList[u]);
  //moves to right spot for append
  while(index(G->adjacencyList[u]) > -1 && v > get(G->adjacencyList[u])){
    moveNext(G->adjacencyList[u]);
  }
  if(index(G->adjacencyList[u]) == -1){
    append(G->adjacencyList[u], v);
  }
  else{
    insertBefore(G->adjacencyList[u], v);
  }
  G->size++;
}

//void BFS(Graph G, int s) - runs BFS algorithm on Graph G with source S, setting color, distance, parent, and source fields of G.
//based on pseudocode provided
void BFS(Graph G, int s){
  if(G==NULL){
    printf("Graph Error: Calling BFS() on a NULL Graph");
    exit(1);
  }
  G->source = s;
  //sets all to default values
  for(int i = 0; i <= getOrder(G); i++){
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  //creates queue
  List Q = newList();
  G->color[s] = GREY;
  G->parent[s] = NIL;
  G->distance[s] = 0;
  //using append list function as a queue, deleteFront as dequeue
  append(Q, s);

  while(length(Q) > 0){
    int temp = front(Q);
    deleteFront(Q);
    moveFront(G->adjacencyList[temp]);
    while(index(G->adjacencyList[temp]) > -1){
      int u = get(G->adjacencyList[temp]);
      if(G->color[u] == WHITE){
        G->color[u] = GREY;
        G->parent[u] = temp;
        G->distance[u] = G->distance[temp] + 1;
        append(Q, u);
      }
      moveNext(G->adjacencyList[temp]);
    }
    G->color[temp] = BLACK;
  }
  freeList(&Q);
}
//void printGraph(FILE* out, Graph G) - Prints out the graph
void printGraph(FILE* out, Graph G){
  if(G==NULL){
    printf("Graph Error: Calling getPath() on a NULL Graph");
    exit(1);
  }
  for(int i = 0; i<getOrder(G); i++){
    fprintf(out, "%d:", i);
    printList(out, G->adjacencyList[i]);
    fprintf(out, "\n");
  }
}
