#include <stdio.h>
#include <stdlib.h>
#include "jval.h"
#include "dllist.h"
#include "jrb.h"

typedef Jval State;

State makeState(unsigned int x, unsigned int y) {
  return new_jval_i( (x << 8) + y);
}

unsigned int getX(State s) {
  return jval_i(s) >> 8;
}

unsigned int getY(State s) {
  return jval_i(s) & 255;
}

void printState(State s) {
  printf("(%d,%d)", getX(s), getY(s));
}

int isEqual(State a, State b) {
  return (getX(a) == getX(b)) && (getY(a) == getY(b)) ;
}

State initialState() {
  return makeState(0,0);
}

int isFinalState(State s) {
  return (getX(s) == 2) || (getY(s) == 2);
}

int isMember(State s, Dllist l) {
  Dllist i;
  dll_traverse(i, l) {
    if (isEqual(dll_val(i), s)) return 1;
  }
  return 0;
}

Dllist getNextStates(State s) {
  int x, y;
  Dllist r = new_dllist();
  x = getX(s);
  y = getY(s);
  dll_append(r, makeState(0,y));
  dll_append(r, makeState(x, 0));
  dll_append(r, makeState(3, y));
  dll_append(r, makeState(x, 4));
  if (x + y <= 4)
    dll_append(r, makeState(0, x + y));
  else
    dll_append(r, makeState(x + y - 4, 4));
  if (x + y <= 3)
    dll_append(r, makeState(x + y, 0));
  else
    dll_append(r, makeState(3, x + y - 3));
  return r;
}

void printResult(State s, JRB parent) {
  Dllist i;
  Dllist l = new_dllist();
  JRB n;
  dll_prepend(l, s);
  while ( (n = jrb_find_int(parent, jval_i(s))) != NULL) {
    dll_prepend(l, n->val);
    s = n->val;
  }
  dll_traverse(i, l) {
    printState(dll_val(i));
    printf(" => ");
  }
  printf("\n");
  free_dllist(l);
}

void BFS() {
  State s, sn;
  Dllist open, close, n, nextStates;
  JRB parent;

  open = new_dllist();
  close = new_dllist();
  parent = make_jrb();

  dll_append(open, initialState());

  while(!dll_empty(open)) {
    n = dll_first(open);
    s = dll_val(n);
    dll_delete_node(n);
    
    if (isFinalState(s)) {
      printResult(s, parent);
      break;
    }
    dll_append(close, s);
    
    nextStates = getNextStates(s);
    dll_traverse(n, nextStates) {
      sn = dll_val(n);
      if (!isMember(sn, open) && !isMember(sn, close)) {
	dll_append(open, sn);
	jrb_insert_int(parent, jval_i(sn), s);
      }
    }
    free_dllist(nextStates);
  }
  
}

int main() {
  BFS();
  return 0;
}
