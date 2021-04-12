#include <stdio.h>
#include <stdlib.h>
#include "graphjrb.h"
Graph createGraph(){
  Graph gr;
  gr=make_jrb();
  return gr;
}
void addEdge(Graph graph, int v1, int v2){
  JRB tree,tree2,node;
  node = jrb_find_int(graph, v1);
  if(node==NULL){
    tree = make_jrb();
    jrb_insert_int(graph, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_i(1));
  }
  else {
    tree = (JRB) jval_v(node->val);
    jrb_insert_int(tree, v2, new_jval_i(1));
  }
  node = jrb_find_int(graph, v2);
  if(node==NULL){
    tree2 = make_jrb();
    jrb_insert_int(graph, v2, new_jval_v(tree2));
    jrb_insert_int(tree2, v1, new_jval_i(1));
  }
  else {
    tree2 = (JRB) jval_v(node->val);
    jrb_insert_int(tree2, v1, new_jval_i(1));
  }
}
int adjecent(Graph graph,int v1,int v2){
  JRB node;
  node=jrb_find_int(graph,v1);
  if(node==NULL) return 0;
  else return jval_i(jrb_find_int((JRB)node->val,v2))->val);
}
int getAdjacentVertices(Graph graph,int vertex,int* output){
  int n=0,i;
  JRB node,*ptr;
  node=jrb_find_int(graph,v1);
  if(node==NULL) return 0;
  else {
    jrb_traverse(ptr,node->val) n++;
  }
  return n;
}
  void dropGraph(Graph graph){
    jrb_free_tree(graph);
    return;
  }
