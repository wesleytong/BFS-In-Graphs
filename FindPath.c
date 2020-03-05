/****************************************************************************************
*  Wesley Tong
*  PA4
*  wtong5
*  Graph.c
*  Implemetation file for FindPath.c
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 255

int main(int argc, char* argv[]){
  FILE *in, *out;
  char line[MAX_LEN];
  //checks command line for correct number of arguments
  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");

  //fgets(line, MAX_LEN, in);

  //vertices (size)
  int vertices;
  fscanf(in, "%d", &vertices);
  Graph G = newGraph(vertices);

  //edges
  while(fgets(line, MAX_LEN, in) != NULL){
    int u = 0;
    int v = 0;
    fscanf(line, "%d %d", &u, &v);
    if(u!=0 && v != 0){
      addEdge(G, u, v);
    }
  }

  //for the result of path:
  List L = newList();
  int source = 0;
  int destination = 0;
  while(fgets(line, MAX_LEN, in) != NULL){
    fscanf(in, "%d %d", &source, &destination);
    if(source !=0 && destination != 0){
      BFS(G, source);
      getPath(L, G, destination);
      //prints first line for distance in output file
      fprintf(out, "The distance from %d to %d is ");
      int distance = getDist(G, destination);
      if(distance == INF){
        fprintf(out, "infinity\n");
      }
      else{
        fprintf(out, "%d\n", distance);
      }
      //prints second line for the shortest path
      getPath(L, G, source);
      if(front(L) == NULL){
        fprintf(out, "No %d-%d path exists", source, destination);
      }
      else{
        fprintf(out, "A shortest %d-%d path is: ", source, destination);
        printList(out, L);
      }
    }
    clear(L);
  }

  printGraph(out, G);
  freeGraph(&G);
  freeList(&L);
  fclose(in);
  fclose(out);
}
