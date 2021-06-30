#include <stdio.h>
#include "graphjrb.h"
void printVertex(int v) {
  printf("%4d", v);
}
int main(){
  Dllist shortest,ptr;
  shortest= new_dllist();
  Graph g = createGraph();
  addEdge(g, 0, 1);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 2, 3);
  addEdge(g, 2, 4);
  addEdge(g, 4, 5);
  printf("\nBFS: start from node 1 to 4 : ");
  BFS(g, 1,4, printVertex);
  printf("\nBFS: start from node 1 to all : ");
  BFS(g, 1, -1, printVertex);
  printf("\n");
  printf("\nDFS: start from node 1 to 4 : ");
  DFS(g, 1, 4, printVertex);
  printf("\nDFS: start from node 1 to all : ");
  DFS(g, 1, -1, printVertex);
  printf("\n");
  ShortestPath(g,1,4,shortest);
  printf("Shortest Path start from node 1 to 4: ");
  dll_traverse(ptr,shortest) printf("%d ",jval_i(ptr->val));
  if(isInDll(shortest,3)) printf("Yes\n");
  else printf("No\n");
  printf("\n");
  return 0;
}

