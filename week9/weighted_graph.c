#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "weighted_graph.h"
Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}
void addVertex(Graph graph, int id, char *name)
{
    JRB find = jrb_find_int(graph.vertices, id);
    if (find == NULL)
    {
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
    }
    else
        find->val = new_jval_s(name);
    return;
}
int getVertexId(Graph graph, char *name)
{
    JRB i;

    jrb_traverse(i, graph.vertices)
    {
        if (strcmp(name, jval_s(i->val)) == 0)
            return jval_i(i->key);
    }
    return -1;
}
char *getVertexName(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.vertices, id);
    if (node != NULL)
        return jval_s(node->val);
    else
        return NULL;
}
void addEdge(Graph graph, int v1, int v2, double w)
{
    if (getVertexName(graph, v1) == NULL || getVertexName(graph, v1) == NULL)
    {
        printf("invalid vertices!\n");
        return;
    }
    else
    {
        JRB tree, node;
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(tree, v2, new_jval_d(w));
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
            jrb_insert_int(tree, v2, new_jval_d(w));
        }
    }
}
int hasEdge(Graph graph, int v1, int v2)
{
    JRB node, node2;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    else
    {
        node2 = jrb_find_int((JRB)jval_v(node->val), v2);
        if (node2 == NULL)
            return 0;
        else
            return 1;
    }
}
double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, node2;
    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return INFINITIVE_VALUE;
    else
    {
        node2 = jrb_find_int((JRB)jval_v(node->val), v2);
        if (node2 == NULL)
            return INFINITIVE_VALUE;
        else
            return jval_d(node2->val);
    }
}
int indegree(Graph graph, int v, Dllist output)
{
    int n = 0, i;
    JRB ptr, ptr2, node;
    if (getVertexName(graph, v) == NULL)
        return 0;
    else
    {
        jrb_traverse(ptr, graph.edges)
        {
            node = (JRB)jval_v(ptr->val);
            jrb_traverse(ptr2, node)
            {
                if (jval_i(ptr2->key) == v)
                {
                    dll_append(output, ptr->key);
                    n++;
                }
            }
        }
    }
    return n;
}
int outdegree(Graph graph, int v, Dllist output)
{
    int n = 0, i;
    JRB node, ptr, node2;
    node = jrb_find_int(graph.edges, v);
    if (node == NULL)
        return 0;
    else
    {
        node2 = (JRB)jval_v(node->val);
        jrb_traverse(ptr, node2)
        {
            dll_append(output, ptr->key);
            n++;
        }
    }
    return n;
}
void BFS(Graph g, int start, int stop, void (*func)(int))
{
    Dllist queue = new_dllist(), node;
    dll_append(queue, new_jval_i(start));
    JRB find1, find2, ptr, visited = make_jrb();
    int v;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        v = jval_i(node->val);
        dll_delete_node(node);
        find1 = jrb_find_int(g.edges, v);
        if (jrb_find_int(visited, v) == NULL)
        {
            func(v);
            jrb_insert_int(visited, v, new_jval_i(1));
            if (find1 != NULL)
            {
                find2 = (JRB)jval_v(find1->val);
                jrb_traverse(ptr, find2)
                {
                    if (jrb_find_int(visited, jval_i(ptr->key)) == NULL)
                        dll_append(queue, new_jval_i(jval_i(ptr->key)));
                }
            }
        }
        if (v == stop)
            break;
    }
    jrb_free_tree(visited);
    free_dllist(queue);
}
void DFS(Graph g, int start, int stop, void (*func)(int))
{
    Dllist stack = new_dllist(), node;
    dll_prepend(stack, new_jval_i(start));
    JRB find1, find2, ptr, visited = make_jrb();
    int v;
    while (!dll_empty(stack))
    {
        node = dll_first(stack);
        v = jval_i(node->val);
        dll_delete_node(node);
        find1 = jrb_find_int(g.edges, v);
        if (jrb_find_int(visited, v) == NULL)
        {
            func(v);
            jrb_insert_int(visited, v, new_jval_i(1));
            if (find1 != NULL)
            {
                find2 = (JRB)jval_v(find1->val);
                jrb_traverse(ptr, find2)
                {
                    if (jrb_find_int(visited, jval_i(ptr->key)) == NULL)
                        dll_prepend(stack, new_jval_i(jval_i(ptr->key)));
                }
            }
        }
        if (v == stop)
            break;
    }
    free_dllist(stack);
    jrb_free_tree(visited);
}
JRB initVertex(Graph g){
  JRB v=make_jrb();
  JRB ptr;
  vertex *ver;
  jrb_traverse(ptr,g.vertices){
    ver=(vertex*)malloc(sizeof(vertex));
    ver->d=INFINITIVE_VALUE;
    ver->parent=-1;
    jrb_insert_int(v,jval_i(ptr->key),new_jval_v(ver));
  }
  return v;
}
void dropVertexTree(JRB v){
  JRB ptr;
  vertex* ver;
  jrb_traverse(ptr,v){
    ver=(vertex*)jval_v(ptr->val);
    free(ver);
  }
  jrb_free_tree(v);
  return;
}
double getd(JRB tree,int v){
  vertex * ver;
  JRB find=jrb_find_int(tree,v);
  if(find!=NULL){
    ver=(vertex*)jval_v(find->val);
    return ver->d;
  }
  else return -1;
}
int  getParent(JRB tree,int v){
  vertex *ver;
  JRB ptr,find=jrb_find_int(tree,v);
  if(find!=NULL){
    ver=(vertex*)jval_v(find->val);
    return ver->parent;
  }
  else return -1;
}
void setVertexd(JRB tree,int v,double d){
  JRB find,find2;
  vertex *ver,ver2;

  find=jrb_find_int(tree,v);
  if(find!=NULL){
    ver=(vertex*)jval_v(find->val);
    ver->d=d;
  }
}
void setVertexParent(JRB tree,int v,int p){
  JRB find;
  vertex *ver;
  find=jrb_find_int(tree,v);
  if(find!=NULL){
    ver=(vertex*)jval_v(find->val);
    ver->parent=p;
  }
}
double shortestPath(Graph graph, int s, int t, Dllist path, int *length)
{
    JRB ptr, vertex;
    JRB visited = make_jrb();
    Dllist i, save,q = new_dllist();
    int min,u,index;
    double p=0,min2;
    *length=0;
    vertex=initVertex(graph);
    setVertexd(vertex,s,0);
    dll_append(q, new_jval_i(s));
    while (!dll_empty(q))
    {
      min2=INFINITIVE_VALUE;
      dll_traverse(i, q)
        {
          if(getd(vertex,jval_i(i->val))<=min2) {
            min2=getd(vertex,jval_i(i->val));
            min=jval_i(i->val);
            save=i;
          }
        }
      if(min==t){
        index=min;
        do{
          dll_prepend(path,new_jval_i(index));
          *length++;
          p+=getEdgeValue(graph,getParent(vertex,index),index);
          index=getParent(vertex,index);
        }while(index!=s);
        dll_prepend(path,new_jval_i(s));
        dropVertexTree(vertex);
        free_dllist(q);
        jrb_free_tree(visited);
        return p;
      }
      dll_delete_node(save);
      if (jrb_find_int(visited,min) == NULL){
        jrb_insert_int(visited, min,new_jval_i(1));
        jrb_traverse(ptr, graph.vertices)
          {
            if (hasEdge(graph, min, jval_i(ptr->key)))
              {
                u=jval_i(ptr->key);
                if (getd(vertex,u) > getd(vertex,min) + getEdgeValue(graph,min,u))
                  {
                    setVertexd(vertex,u,getd(vertex,min) + getEdgeValue(graph,min,u));
                    setVertexParent(vertex,u,min);
                  }

                if (jrb_find_int(visited,u) == NULL)
                  dll_append(q, new_jval_i(u));
              }
          }
      }
    }
    dropVertexTree(vertex);
    free_dllist(q);
    jrb_free_tree(visited);
    return INFINITIVE_VALUE;
}
int onCycle(Graph graph, int v)
{
  Dllist queue = new_dllist(), node;
  dll_append(queue, new_jval_i(v));
  JRB find1, find2, ptr, visited = make_jrb();
  int i;
    while (!dll_empty(queue))
    {
        node = dll_first(queue);
        i = jval_i(node->val);
        dll_delete_node(node);
        find1 = jrb_find_int(graph.edges, i);
        if (jrb_find_int(visited, i) == NULL)
        {
            jrb_insert_int(visited, i, new_jval_i(1));
            if (find1 != NULL)
            {
                find2 = (JRB)jval_v(find1->val);
                jrb_traverse(ptr, find2)
                {
                    if (jrb_find_int(visited, jval_i(ptr->key)) == NULL)
                        dll_append(queue, new_jval_i(jval_i(ptr->key)));
                    if (hasEdge(graph, jval_i(ptr->key), v))
                    {
                        jrb_free_tree(visited);
                        free_dllist(queue);
                        return 1;
                    }
                }
            }
        }
    }
    jrb_free_tree(visited);
    free_dllist(queue);
    return 0;
}
int isDAG(Graph graph)
{
    JRB node;
    jrb_traverse(node, graph.vertices)
    {
        if (onCycle(graph, jval_i(node->key)))
            return 0;
    }
    return 1;
}
Dllist Tsort(Graph graph)
{
    JRB tb, ptr;
    int i, v;
    Dllist node, l = new_dllist();
    Dllist q = new_dllist();
    Dllist output = new_dllist();
    tb = make_jrb();
    jrb_traverse(ptr, graph.vertices)
    {
        i = indegree(graph, jval_i(ptr->key), l);
        jrb_insert_int(tb, jval_i(ptr->key), new_jval_i(i));
    }
    jrb_traverse(ptr, tb)
    {
        if (jval_i(ptr->val) == 0)
            dll_append(q, new_jval_i(jval_i(ptr->key)));
    }
    while (!dll_empty(q))
    {
        node = dll_first(q);
        v = jval_i(node->val);
        dll_delete_node(node);
        dll_append(output, new_jval_i(v));
        jrb_traverse(ptr, tb)
        {
            if (hasEdge(graph, v, jval_i(ptr->key)))
            {
                ptr->val = new_jval_i(jval_i(ptr->val) - 1);
                if (jval_i(ptr->val) == 0)
                    dll_append(q, new_jval_i(jval_i(ptr->key)));
            }
        }
    }
    free_dllist(q);
    free_dllist(l);
    jrb_free_tree(tb);
    return output;
}
void dropGraph(Graph graph)
{
    JRB i;

    jrb_traverse(i, graph.vertices)
    {
        free(jval_v(i->val));
    }
    jrb_free_tree(graph.vertices);
    jrb_traverse(i, graph.edges)
        jrb_free_tree((JRB)jval_v(i->val));
    jrb_free_tree(graph.edges);
}
