/****************************************************************************************
*  Wesley Tong
*  PA4
*  wtong5
*  GraphTest.c
*  Test file for Graph.c
*****************************************************************************************/
#include<stdio.h>
#include "Graph.h"

int main(int argc, char* argv[]){
  int n = 20;
  Graph A = newGraph(n);

  printf("Size: %d\n", getSize(A));
  printf("Source: %d\n", getSource(A));
  printf("Order: %d\n", getOrder(A));
  printf("Parent of 1: %d\n", getParent(A,1));
  printf("Distance: %d\n", getDist(A,1));
  printf("\n");
/*
  addEdge(A,1,5);
  addEdge(A,3,2);
  addEdge(A,3,5);
  addEdge(A,5,6);
  addEdge(A,2,5);
  addEdge(A,4,3);
  addEdge(A,7,2);
  addEdge(A,19,5);
  addEdge(A,11,7);
  addEdge(A,14,19);
  addEdge(A,15,13);
  addEdge(A,9,18);
  addEdge(A,13,20);
  addEdge(A,20,6);
  addEdge(A,2,8);
  addEdge(A,19,5);
  addEdge(A,20,6);
  addEdge(A,15,5);
  printGraph(stdout, A);
*/
addEdge(A,1,2);
    addEdge(A,1,3);
    addEdge(A,2,4);
    addEdge(A,2,5);
    addEdge(A,2,6);
    addEdge(A,3,4);
    addEdge(A,4,5);
    addEdge(A,5,6);
    printGraph(stdout, A);
  printf("Size: %d\n", getSize(A));
  printf("Source: %d\n", getSource(A));
  printf("Order: %d\n", getOrder(A));
  printf("Parent of 1: %d\n", getParent(A,1));
  printf("Distance: %d\n", getDist(A,1));
  printf("\n");

  BFS(A, 1);
  printf("Source: %d\n", getSource(A));
  printf("Parent of 1: %d\n", getParent(A, 1));
  printf("Parent of 2: %d\n", getParent(A, 2));
  printf("Parent of 3: %d\n", getParent(A, 3));
  printf("Distance (1,1): %d\n", getDist(A, 1));
  printf("Distance (1,2): %d\n", getDist(A, 2));
  printf("Distance (1,3): %d\n", getDist(A, 3));
  printf("\n");

  makeNull(A);
  printGraph(stdout, A);
  freeGraph(&A);
}
