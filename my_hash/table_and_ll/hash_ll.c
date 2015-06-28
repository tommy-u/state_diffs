#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "utlist.h"
//Provides basic functionality for hashing and adding ids to linked list for ints
//Need to implement mpz to int key bit packing
//Need to implement linked list when have hash collision.

//The struct we want to hash.
typedef struct { 
  int key;
  long payload;
  int id;
  int count;
  UT_hash_handle hh;
} record_t;

typedef struct el {
  int id;
  struct el *next, *prev;
} el;

record_t *records = NULL;
el *head = NULL;

void ll_add(int id){
  el *ent = (el*)malloc(sizeof(el));
  ent->id = id;
  DL_APPEND(head, ent);
}

void hash_add(int key, long payload, int *id_ctr){
  record_t *s;
  HASH_FIND(hh, records, &key, sizeof(int),s);
  //When true, no record with same key exists
  if(s==NULL)
    {
      record_t *r = (record_t*)malloc( sizeof(record_t) );
      memset(r, 0, sizeof(record_t));
      r->key=key;
      r->payload=payload;
      r->id=(*id_ctr)++;
      r->count=1;
      HASH_ADD(hh, records, key, sizeof(int), r);
      ll_add(r->id);
    }
  else
    {
      //record with same key exists. need to find out if it's the same payload
      if (s->payload == payload)
	{
	  s->count++;
	  ll_add(s->id);
	}
      else
	{
	  //key collision for different payloads...what to do?
	  //kinda want to linear probe. maybe chaining
	  

	}
      
    }
}

void hash_find(int key){
  record_t l, *p;
  memset(&l, 0, sizeof(record_t));
  l.key=key;
  HASH_FIND(hh, records, &l.key, sizeof(int), p);
  if (p) {
    printf("found that item\n");
  }
  else{
    printf("didn't find the item\n");
  }
}

int main() {
  int id_ctr = 1;
  record_t *p, *tmp;
  el *elt, *el_tmp;
  hash_add(5, 1243, &id_ctr);
  hash_add(4, 3456, &id_ctr);
  hash_add(6, 2345, &id_ctr);
  hash_add(6, 2345, &id_ctr);

  
  printf("hash table \n");
  HASH_ITER(hh, records, p, tmp) {
    printf("key %d, payload %ld, id %d, count %d \n", p->key, p->payload, p->id, p->count);
    HASH_DEL(records, p);
    free(p);
  }

  printf("linked list \n");
  DL_FOREACH(head,elt) 
    printf("%d\n", elt->id);

  DL_FOREACH_SAFE(head,elt,el_tmp) {
    DL_DELETE(head,elt);
    free(elt);
  }
  
  return 0;  
}
