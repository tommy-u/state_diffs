#include <stdlib.h>
#include <stdio.h>
#include "uthash.h"
#include "gmp.h"

typedef struct {
  mpz_t my_mpz;
} record_t_key;

typedef struct { 
  record_t_key key;
  int id;
  UT_hash_handle hh;
} record_t;

int main(int argc, char *argv[]) {
  record_t l, *p, *r, *tmp, *records = NULL;

  //build the record itself
  r = (record_t*)malloc( sizeof(record_t) );
  memset(r, 0, sizeof(record_t));
  
  //create an mpz
  //Are there multiple ways to write the same value, 4?
  mpz_t my_z; mpz_init_set_ui(r->key.my_mpz,4);
  HASH_ADD(hh, records, key, sizeof(record_t_key), r);
  
  //build a matching key to use to find the record
  memset(&l, 0, sizeof(record_t));
  //create an mpz
  mpz_t z_tmp; mpz_init_set_ui(l.key.my_mpz,4);

  HASH_FIND(hh, records, &l.key, sizeof(record_t_key), p);
  
  if (p) 
    {
      printf("found that item\n");
    }else{
    printf("did not find item \n");
  }

  printf("r->key.my_mpz \n");
  mpz_out_str(stdout,2,r->key.my_mpz);
  printf("\n");

  printf("l.key.my_mpz \n");
  mpz_out_str(stdout,2,l.key.my_mpz);
  printf("\n");

  printf("size of r->key %lu\n", sizeof(r->key));
  
  char *a = &(r->key);
  int i;
  printf("bytes of r->key");
  for (i=0;i<sizeof(r->key); i++)
    printf("%c \n", *(a+i));
  
  a = &(l.key);
  printf("bytes of l.key");
  for (i=0;i<sizeof(r->key); i++)
    printf("%c \n", *(a+i));
 

  HASH_ITER(hh, records, p, tmp) {
    HASH_DEL(records, p);
    free(p);
  }

  return 0;  
}
