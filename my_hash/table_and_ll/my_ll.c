#include <stdio.h>
#include <stdlib.h>
#include "utlist.h"

typedef struct el {
  int val;
  struct el *next, *prev;
} el;

el *head = NULL;

void add(int val){
  el *ent = (el*)malloc(sizeof(el));
  ent->val = val;
  DL_APPEND(head, ent);
}

int main(int argc, char *argv[]) {  
  el *elt, *tmp;
  add(5);
  add(10);
  add(5);

  DL_FOREACH(head,elt) printf("%d\n", elt->val);

  DL_FOREACH_SAFE(head,elt,tmp) {
    DL_DELETE(head,elt);
    free(elt);
  }

  return 0;
}
