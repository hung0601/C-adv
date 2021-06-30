#include "jrb.h"
#include "dllist.h"
#define INFINITIVE_VALUE 10000000
typedef struct {
  JRB edges;
  JRB vertices;
} Graph;
typedef struct vertex{
  double d;
  int parent;
}vertex;
Graph createGraph();
void addVertex(Graph graph, int id, char* name);
int getVertexID(Graph graph,char * name);
char *getVertexName(Graph graph,int id);
void addEdge(Graph graph, int v1, int v2,double w);
int hasEdge(Graph graph, int v1, int v2);
double getEdgeValue(Graph graph, int v1, int v2);
int  indegree(Graph graph, int v,Dllist output);
int  outdegree(Graph graph, int v,Dllist output);
void BFS(Graph g, int start, int stop, void (*func)(int));
void DFS(Graph g, int start, int stop, void (*func)(int));
JRB initVertex(Graph g);
void dropVertexTree(JRB v);
double getd(JRB tree,int v);
int  getParent(JRB tree,int v);
void setVertexd(JRB tree,int v,double d);
void setVertexParent(JRB tree,int v,int p);
double shortestPath(Graph graph, int s, int t,Dllist path,int*length);
int isAcycle(Graph graph,int v);
int isDAG(Graph graph);
Dllist Tsort(Graph graph);
void dropGraph(Graph graph);
