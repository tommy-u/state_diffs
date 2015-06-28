#include <stdio.h>
#include <stdlib.h>
#include "utlist.h"
//trace elements
typedef struct te {
  int id;
  struct te *next, *prev;
} te;

//associative list val to id
typedef struct aa {
  int id;
  int val;
  struct aa *next, *prev;
} aa;

te *head_te = NULL;
aa *head_aa = NULL;
//first one will be 1 due to increment
int id = 0;

void add_trace_element(int id){
  te *ent = (te*)malloc(sizeof(te));
  ent->id = id;
  DL_APPEND(head_te, ent);
}

void add_state(int val){
  //given a value, do we need to add it to the associative list?
  aa *ait, atmp;
  atmp.val=val;
  DL_SEARCH(head_aa,ait,&atmp,associative_cmp);
  //if we find it, nothing to do here
  //if we don't find it, need to grab a new id and make an association
  
  if (ait){
    add_trace_element(ait->id);
  }
  else {
   
    aa *ant = (aa*)malloc(sizeof(te));
    ant->val=val;
    //add first so we can use id below
    ant->id=++id;
    DL_APPEND(head_aa, ant);
    add_trace_element(id);
  }
}

//havent thought about this
int associative_cmp(aa *a, aa *b){
  if ( a->val > b->id )
    return 1;
  if ( a->val < b->id )
    return -1;
  return 0;
}

//havent thought about this
int id_cmp(te *a, te *b) {
  if (a->id > b->id)
    return 1;
  if (a->id < b->id)
    return -1;
  return 0;
}


void spool_id_trace(){
  te *elt;
  DL_FOREACH(head_te,elt) printf("%d\n", elt->id); 
}

void spool_association(){
  aa *alt;
  DL_FOREACH(head_aa,alt) printf("id %d, val %d \n", alt->id, alt->val); 
}

int main(){
  add_state(5);
  add_state(10);
  add_state(1);
  add_state(5);
  add_state(3);
    
  spool_id_trace();
  spool_association();
  te *elt, *tmp_te;
  aa *alt, *tmp_aa;
  
  DL_FOREACH_SAFE(head_te,elt,tmp_te) {
    DL_DELETE(head_te,elt);
    free(elt);
  }
  DL_FOREACH_SAFE(head_aa,alt,tmp_aa) {
    DL_DELETE(head_aa,alt);
    free(alt);
  }     
  
  return 0;
}
/*
te *elt, *tmp, etmp;
add_trace_element(5);
add_trace_element(10);
add_trace_element(5);

etmp.id=5;
//head , tmp pointer , address 
DL_SEARCH(head_te,elt,&etmp,id_cmp);
if (elt) printf("found it\n"); else printf("did not find it\n");

etmp.id=8;
DL_SEARCH(head_te,elt,&etmp,id_cmp);
if (elt) printf("found it\n"); else printf("did not find it\n");
  
DL_FOREACH(head_te,elt) printf("%d\n", elt->id);

			DL_FOREACH_SAFE(head_te,elt,tmp) {
			  DL_DELETE(head_te,elt);
			  free(elt);
			}

return 0;
}
*/
