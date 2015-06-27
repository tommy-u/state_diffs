//This version attmepts to use single struct
#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "gmp.h"
//Hash obj
typedef struct { 
  mpz_t key;
  int id;
  UT_hash_handle hh;
} record_t;

int main(int argc, char *argv[]) {
  record_t l, *p, *r, *tmp, *records = NULL;

  //build the record itself
  r = (record_t*)malloc( sizeof(record_t) );
  memset(r, 0, sizeof(record_t));
  //create an mpz
  mpz_t my_z; mpz_init(my_z); mpz_set_str(my_z, "110", 2);

  mpz_init_set(r->key, my_z);
  HASH_ADD(hh, records, key, sizeof(mpz_t), r);
  
  //build a matching key to use to find the record
  memset(&l, 0, sizeof(record_t));
    //create an mpz
  mpz_t z_tmp; mpz_init(z_tmp); mpz_set_str(z_tmp, "110", 2);
  mpz_init_set(l.key, z_tmp);

  HASH_FIND(hh, records, &l.key, sizeof(mpz_t), p);
 
  if (p) 
    {
      printf("found that item\n");
    }

  printf("r->key.my_mpz \n"); mpz_out_str(stdout,2,r->key); printf("\n");

  printf("l.key.my_mpz \n"); mpz_out_str(stdout,2,l.key); printf("\n");
 
  printf("table element mpz "); mpz_out_str(stdout,2,records->key); printf("  records->id %d \n",records->id);
  printf("num entries = %d \n",HASH_COUNT(records));
  HASH_ITER(hh, records, p, tmp) {
    HASH_DEL(records, p);
    free(p);
  }

  return 0;  
}
