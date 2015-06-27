//Prove what you're trying to do in 2 is possible with a simpler structure.
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "utlist.h"
//The struct we want to hash.
typedef struct { 
  int key;
  int id;
  int count;
  UT_hash_handle hh;
} record_t;

record_t l, *p, *r, *tmp, *records = NULL;
int id_ctr = 1;

void add(int key){
  record_t *s;
  HASH_FIND(hh, records, &key, sizeof(int),s);
  //When true, record is absent
  if(s==NULL)
    {
      r = (record_t*)malloc( sizeof(record_t) );
      memset(r, 0, sizeof(record_t));
      r->key=key;
      r->id=id_ctr++;
      r->count=1;
      HASH_ADD(hh, records, key, sizeof(int), r);
    }
  else
    {
      s->count++;
    }
}

record_t * find(int key){
  memset(&l, 0, sizeof(record_t));
  l.key=key;
  HASH_FIND(hh, records, &l.key, sizeof(int), p);
  return p;
}

int main(int argc, char *argv[]) {
  add(5);
  add(4);

  //Check to see if you found the item
  if (find(5)) {
    printf("found that item\n");
  } 
  else{
    printf("didn't find the item\n");
  }
  
  if (find(4)) {
    printf("found that item\n");
  } 
  else{
    printf("didn't find the item\n");
  }
  
  HASH_ITER(hh, records, p, tmp) {
    printf("key %d, id %d, count %d \n", p->key, p->id, p->count);
    HASH_DEL(records, p);
    free(p);
  }
  
  return 0;  
}
