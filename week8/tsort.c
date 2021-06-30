#include <stdio.h>
#include "directed_graph.h"
int main(){
  Dllist ouput,ptr;
  Graph g = createGraph();
  addVertex(g, 0, "CS102"); addVertex(g, 1, "CS140");
  addVertex(g, 2, "CS160"); addVertex(g, 3, "CS302");
  addVertex(g, 4, "CS311"); addVertex(g, 5, "MATH300");
  addEdge(g, 0, 1); addEdge(g, 0, 2);
  addEdge(g, 1, 3); addEdge(g, 5, 4); addEdge(g, 3, 4);
  if (!isDAG(g)) {
    printf("Can not make topological sort\n");
    return 1; }
  ouput=Tsort(g);
  printf("The topological order:\n");
  dll_traverse(ptr,ouput)
    printf("%s\n", getVertexName(g,jval_i(ptr->val)));
  return 0;
}
