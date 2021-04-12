#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
Graph createGraph(int sizemax){
  Graph gr;
  gr.sizemax=sizemax;
  gr.matrix=malloc(sizeof(int)*sizemax*sizemax);
  for(int i=0;i<sizemax*sizemax;i++) gr.matrix[i]=0;
  return gr;
}
void addEdge(Graph graph, int v1, int v2){
  graph.matrix[v1*graph.sizemax+v2]=1;
  graph.matrix[v2*graph.sizemax+v1]=1;
}
int adjecent(Graph graph,int v1,int v2){
  return graph.matrix[v1*graph.sizemax +v2];
}
int getAdjacentVertices(Graph graph,int vertex,int* output){
  int n=0,i;
  for(i=0;i<graph.sizemax;i++){
    if(adjecent(graph,vertex,i)) output[n++]=i;
  }
  return n;
}
  void dropGraph(Graph graph){
    free(graph.matrix);
    return;
  }
  
  
