#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "directed_graph.h"
Graph createGraph(){
  Graph g;
  g.edges=make_jrb();
  g.vertices=make_jrb();
  return g;
}
void addVertex(Graph graph,int id,char * name){
  JRB find=jrb_find_int(graph.vertices,id);
  if(find==NULL){
    jrb_insert_int(graph.vertices, id,new_jval_s(strdup(name)));
  }
  else find->val=new_jval_s(name);
  return;
}
int getVertexId(Graph graph, char *name) {
  JRB i;

  jrb_traverse(i, graph.vertices) {
    if (strcmp(name, jval_s(i->val)) == 0)
      return jval_i(i->key);
  }
  return -1;
}
char *getVertexName(Graph graph, int id) {
  JRB node = jrb_find_int(graph.vertices, id);
  if (node != NULL)
    return jval_s(node->val);
  else return NULL;
}
void addEdge(Graph graph, int v1,int v2){
  if(getVertexName(graph,v1)==NULL || getVertexName(graph,v1)==NULL){
    printf("invalid vertices!\n");
    return;
  }
  else{
    JRB tree,node;
    node = jrb_find_int(graph.edges, v1);
    if(node==NULL){
      tree = make_jrb();
      jrb_insert_int(tree, v2, new_jval_i(1));
      jrb_insert_int(graph.edges, v1, new_jval_v(tree));
    }
    else {
      tree = (JRB) jval_v(node->val);
      jrb_insert_int(tree, v2, new_jval_i(1));
    }
  }
}
int hasEdge(Graph graph,int v1,int v2){
  JRB node,node2;
  node=jrb_find_int(graph.edges,v1);
  if(node==NULL) return 0;
  else{
    node2=jrb_find_int((JRB) jval_v(node->val),v2);
    if(node2==NULL) return 0;
    else return jval_i(node2->val);
  }
}

int indegree(Graph graph,int v,Dllist output){
  int n=0,i;
  JRB ptr,ptr2,node;
  if(getVertexName(graph,v)==NULL) return 0;
  else{
    jrb_traverse(ptr,graph.edges){
      node=(JRB) jval_v(ptr->val);
      jrb_traverse(ptr2,node){
        if(jval_i(ptr2->key)==v) {
          dll_append(output,ptr->key);
          n++;
        }
      }
    }
  }
  return n;
}
int outdegree(Graph graph,int v,Dllist output){
  int n=0,i;
  JRB node,ptr,node2;
  node=jrb_find_int(graph.edges,v);
  if(node==NULL) return 0;
  else {
    node2=(JRB) jval_v(node->val);
    jrb_traverse(ptr,node2){
      dll_append(output,ptr->key);
      n++;
    }
  }
  return n;
}
void BFS(Graph g, int start, int stop, void (*func)(int)){
  Dllist queue= new_dllist(),node;
  dll_append(queue, new_jval_i(start));
  JRB find1,find2,ptr,visited= make_jrb();
  int v;
  while(!dll_empty(queue)){
    node = dll_first(queue);
    v = jval_i(node->val);
    dll_delete_node(node);
    find1=jrb_find_int(g.edges,v);
    if(jrb_find_int(visited,v)==NULL){
      func(v);
      jrb_insert_int(visited,v,new_jval_i(1));
      if(find1!=NULL){
        find2=(JRB) jval_v(find1->val);
        jrb_traverse(ptr,find2) {
          if(jrb_find_int(visited,jval_i(ptr->key))==NULL)
            dll_append(queue,new_jval_i(jval_i(ptr->key)));
        }
      }
    }
    if(v==stop) break;
  }
  jrb_free_tree(visited);
  free_dllist(queue);
}
void DFS(Graph g, int start, int stop, void (*func)(int)){
  Dllist stack= new_dllist(),node;
  dll_prepend(stack, new_jval_i(start));
  JRB find1,find2,ptr,visited= make_jrb();
  int v;
  while(!dll_empty(stack)){
    node = dll_first(stack);
    v = jval_i(node->val);
    dll_delete_node(node);
    find1=jrb_find_int(g.edges,v);
    if(jrb_find_int(visited,v)==NULL){
      func(v);
      jrb_insert_int(visited,v,new_jval_i(1));
      if(find1!=NULL){
        find2=(JRB) jval_v(find1->val);
        jrb_traverse(ptr,find2) {
          if(jrb_find_int(visited,jval_i(ptr->key))==NULL)
            dll_prepend(stack,new_jval_i(jval_i(ptr->key)));
        }
      }
    }
    if(v==stop) break;
  }
  free_dllist(stack);
  jrb_free_tree(visited);
}
int onCycle(Graph graph,int v){
  Dllist queue= new_dllist(),node;
  dll_append(queue, new_jval_i(v));
  JRB find1,find2,ptr,visited= make_jrb();
  int i;
  while(!dll_empty(queue)){
    node = dll_first(queue);
    i = jval_i(node->val);
    dll_delete_node(node);
    find1=jrb_find_int(graph.edges,i);
    if(jrb_find_int(visited,i)==NULL){
      jrb_insert_int(visited,i,new_jval_i(1));
      if(find1!=NULL){
        find2=(JRB) jval_v(find1->val);
        jrb_traverse(ptr,find2) {
          if(jrb_find_int(visited,jval_i(ptr->key))==NULL)
            dll_append(queue,new_jval_i(jval_i(ptr->key)));
          if(hasEdge(graph,jval_i(ptr->key),v)) {
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
int isDAG(Graph graph){
  JRB node;
  jrb_traverse(node, graph.vertices) {
    if (onCycle(graph, jval_i(node->key)))
      return 0;
  }
  return 1;
}
Dllist Tsort(Graph graph){
  JRB tb,ptr;
  int i,v;
  Dllist node,l=new_dllist();
  Dllist q=new_dllist();
  Dllist output=new_dllist();
  tb=make_jrb();
  jrb_traverse(ptr,graph.vertices){
    i=indegree(graph,jval_i(ptr->key),l);
    jrb_insert_int(tb,jval_i(ptr->key),new_jval_i(i));
  }
  jrb_traverse(ptr,tb){
    if(jval_i(ptr->val)==0) dll_append(q,new_jval_i(jval_i(ptr->key)));
  }
  while(!dll_empty(q)){
    node = dll_first(q);
    v = jval_i(node->val);
    dll_delete_node(node);
    dll_append(output,new_jval_i(v));
    jrb_traverse(ptr,tb){
      if(hasEdge(graph,v,jval_i(ptr->key))) {
        ptr->val=new_jval_i(jval_i(ptr->val)-1);
        if(jval_i(ptr->val)==0) dll_append(q,new_jval_i(jval_i(ptr->key)));
      }
    }
  }
  free_dllist(q);
  free_dllist(l);
  jrb_free_tree(tb);
  return output;
}
void dropGraph(Graph graph) {
  JRB i;

  jrb_traverse(i, graph.vertices) {
    free(jval_v(i->val));
  }
  jrb_free_tree(graph.vertices);
  jrb_traverse(i, graph.edges)
    jrb_free_tree((JRB)jval_v(i->val));
  jrb_free_tree(graph.edges);
}
