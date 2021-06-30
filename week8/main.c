#include <stdio.h>
#include "directed_graph.h"

void printNode(int key) {
  printf("%d\n", key);
}
int main() {
  Graph g = createGraph();
  addVertex(g, 0, "0");
  addVertex(g, 1, "1");
  addVertex(g, 2, "2");
  addVertex(g, 3, "3");
  addVertex(g, 4, "4");
  addVertex(g, 5, "5");

  addEdge(g, 0, 1);
  addEdge(g, 0, 2);
  addEdge(g, 1, 2);
  addEdge(g, 1, 3);
  addEdge(g, 3, 4);
  addEdge(g, 0, 5);
  addEdge(g, 4, 1);
  DFS(g, 0, -1, printNode);

  if (isDAG(g))
    printf("This is a DAG!\n");
  else
    printf("This is not a DAG!\n");
    dropGraph(g);
  return 0;
}
