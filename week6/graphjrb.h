#include <stdio.h>
#include "dllist.h"
#include "jrb.h"
typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int adjacent(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, int v, int* output);
void BFS(Graph g,int start,int stop,void (*func)(int));
void DFS(Graph g,int start,int stop,void (*func)(int));
int isInDll(Dllist l,int i);
void ShortestPath(Graph g, int start, int stop,Dllist shortest);
void dropGraph(Graph graph);
