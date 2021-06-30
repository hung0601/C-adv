#include <stdio.h>
#include <stdlib.h>
#include "graphjrb.h"
#include "jrb.h"
#include "dllist.h"
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
  JRB node,node2;
  node=jrb_find_int(graph,v1);
  if(node==NULL) return 0;
  else{
    node2=jrb_find_int((JRB) jval_v(node->val),v2);
    if(node2==NULL) return 0;
    else return jval_i(node2->val);
  }
}
int getAdjacentVertices(Graph graph,int vertex,int* output){
  int n=0,i;
  JRB node,ptr,node2;
  node=jrb_find_int(graph,vertex);
  if(node==NULL) return 0;
  else {
    node2=(JRB) jval_v(node->val);
    jrb_traverse(ptr,node2){
     output[n++]=jval_i(ptr->key);
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
    find1=jrb_find_int(g,v);
    if(jrb_find_int(visited,v)==NULL){
      func(jval_i(find1->key));
      jrb_insert_int(visited,v,new_jval_i(1));
      find2=(JRB) jval_v(find1->val);
      jrb_traverse(ptr,find2) {
        if(jrb_find_int(visited,jval_i(ptr->key))==NULL)
          dll_append(queue,new_jval_i(jval_i(ptr->key)));
      }
    }
    if(v==stop) break;
  }
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
    find1=jrb_find_int(g,v);
    if(jrb_find_int(visited,v)==NULL){
      func(jval_i(find1->key));
      jrb_insert_int(visited,v,new_jval_i(1));
      find2=(JRB) jval_v(find1->val);
      jrb_traverse(ptr,find2) {
        if(jrb_find_int(visited,jval_i(ptr->key))==NULL)
          dll_prepend(stack,new_jval_i(jval_i(ptr->key)));
      }
    }
    if(v==stop) break;
  }
}
int isInDll(Dllist l,int i){
  Dllist ptr;
  dll_traverse(ptr,l){
    if(jval_i(ptr->val)==i) return 1;
  }
  return 0;
}
void ShortestPath(Graph g ,int start, int stop,Dllist shortest){
  Dllist queue= new_dllist(),node;
  dll_append(queue, new_jval_i(start));
  JRB find1,find2,ptr,n;
  JRB visited= make_jrb();
  JRB parent= make_jrb();
  int v,p;
  while(!dll_empty(queue)){
    node = dll_first(queue);
    v = jval_i(node->val);
    dll_delete_node(node);
    if(v==stop){
      p=stop;
      dll_prepend(shortest,new_jval_i(p));
      while((n=jrb_find_int(parent,p))!=NULL){
        dll_prepend(shortest,n->val);
        p=jval_i(n->val);
      }
      break;
    }
    find1=jrb_find_int(g,v);
    jrb_insert_int(visited,v,new_jval_i(1));
    find2=(JRB) jval_v(find1->val);
    jrb_traverse(ptr,find2) {
      if(jrb_find_int(visited,jval_i(ptr->key))==NULL && !isInDll(queue,jval_i(ptr->key))){
        jrb_insert_int(parent,jval_i(ptr->key),new_jval_i(v));
        dll_append(queue,new_jval_i(jval_i(ptr->key)));
      }
    }
  }
  jrb_free_tree(visited);
  jrb_free_tree(parent);
  free_dllist(queue);
  return;
}
void dropGraph(Graph graph){
  jrb_free_tree(graph);
  return;
}
