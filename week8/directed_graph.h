#include "jrb.h"
#include "dllist.h"
typedef struct {
  JRB edges;
  JRB vertices;
} Graph;
Graph createGraph();
void addVertex(Graph graph, int id, char* name);
int getVertexID(Graph graph,char * name);
char *getVertexName(Graph graph,int id);
void addEdge(Graph graph, int v1, int v2);
int hasEdge(Graph graph, int v1, int v2);
int  indegree(Graph graph, int v,Dllist output);
int  outdegree(Graph graph, int v,Dllist output);
void BFS(Graph g, int start, int stop, void (*func)(int));
void DFS(Graph g, int start, int stop, void (*func)(int));
int isAcycle(Graph graph,int v);
int isDAG(Graph graph);
Dllist Tsort(Graph graph);
void dropGraph(Graph graph);
