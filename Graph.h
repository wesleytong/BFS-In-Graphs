/****************************************************************************************
*  Wesley Tong
*  PA4
*  wtong5
*  Graph.h
*  Header file for Graph ADT
*****************************************************************************************/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL -2
#include <stdio.h>
#include "List.h"
typedef struct GraphObj* Graph;

//Constructors/Destructors
Graph newGraph(int n); //Creates and returns a Graph with n vertices and no edges
void freeGraph(Graph* pG); //Frees all dynamic memory associated with Graph and sets *pG to NULL

//Access Functions
int getOrder(Graph G); //returns order
int getSize(Graph G); //return size
int getSource(Graph G); //Returns the most recently used source vertex
int getParent(Graph G, int u); //Returns the parent of vertex u in the BFS Tree, or NIL if BFS has not yet been called. pre: 1 <= u <= getOrder(G)
int getDist(Graph G, int u); //Returns the distance from the most recent BFS source to vertex U, or INF if BFS() has not been called. pre: 1 <= u <= getOrder(G)
void getPath(List L, Graph G, int u); //Appends to List L the vertices of a shortest path in G from source to u, or appends to L NIL if no such path exists. pre: getSource(G) != NIL, BFS() must be called before getPath(). 1 <= u <= getOrder(G)

//Manipulation Procedures
void makeNull(Graph G); //Deletes all edges of G, restoring to original no edge state (null graph).
void addEdge(Graph G, int u, int v); //Inserts a new edge joining u to v (u is the adjacency list of v, and v to the adjacency list of u). pre: 1 <= u <= getOrder(G)
void addArc(Graph G, int u, int v); //Inserts a new directed edge from u to v. pre: 1 <= u <= getOrder(G)
void BFS(Graph G, int s); //runs BFS algorithm on Graph G with source S, setting color, distance, parent, and source fields of G.

//Other operations
void printGraph(FILE* out, Graph G); //Prints out the graph


#endif
