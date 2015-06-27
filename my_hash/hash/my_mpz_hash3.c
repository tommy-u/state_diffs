//Prove what you're trying to do in 2 is possible with a simpler structure.
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "gmp.h"
//Switch between modes
#define INTMODE
//#define MPZMODE

//The struct we want to hash.
#ifdef INTMODE
typedef struct { 
  int key;
  int id;
  UT_hash_handle hh;
} record_t;
#endif

#ifdef MPZMODE
typedef struct { 
  mpz_t key;
  int id;
  UT_hash_handle hh;
} record_t;
#endif


int main(int argc, char *argv[]) {
  record_t l, *p, *r, *tmp, *records = NULL;

  //build the record itself
  r = (record_t*)malloc( sizeof(record_t) );
  memset(r, 0, sizeof(record_t));
  //Create an instance of the struct you want to hash.
#ifdef MPZMODE
  mpz_t my_z; mpz_init(my_z); mpz_set_str(my_z, "110", 2);
  mpz_init_set(r->key, my_z);
  HASH_ADD(hh, records, key, sizeof(mpz_t), r);
#endif

#ifdef INTMODE
  r->key=5;
  HASH_ADD(hh, records, key, sizeof(int), r);
#endif

  //Assemble a matching key to use to find the record
  memset(&l, 0, sizeof(record_t));

#ifdef MPZMODE
  //create an mpz
  mpz_t z_tmp; mpz_init(z_tmp); mpz_set_str(z_tmp, "110", 2);
  mpz_init_set(l.key, z_tmp);
  //  mpz_init_set(l.key, my_z); // doesn't work either
  HASH_FIND(hh, records, &l.key, sizeof(mpz_t), p);
#endif 
  
#ifdef INTMODE
  l.key=5;
  HASH_FIND(hh, records, &l.key, sizeof(int), p);
#endif

  //Check to see if you found the item
  if (p) {
  printf("found that item\n");
} else{
  printf("didn't find the item\n");
}



#if 0 //check nothing obvious is broken 
  printf("r->key \n"); mpz_out_str(stdout,2,r->key); printf("\n");

  printf("l.key \n"); mpz_out_str(stdout,2,l.key); printf("\n");
 
  printf("table element mpz "); mpz_out_str(stdout,2,records->key); printf("  records->id %d \n",records->id);
  printf("num entries = %d \n",HASH_COUNT(records));
#endif 
 HASH_ITER(hh, records, p, tmp) {
    HASH_DEL(records, p);
    free(p);
  }

  return 0;  
}
