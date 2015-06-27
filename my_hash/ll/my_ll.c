#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utlist.h"

//contains one name, next and prev pointers
typedef struct el {
  int key;
  struct el *next;
} el;

el *head = NULL; /* important- initialize to NULL! */

int main(int argc, char *argv[]) {
  el *id, *elt, *tmp, etmp;

    if ( (id = (el*)malloc(sizeof(el))) == NULL) exit(-1);
    id->key = 5;
    DL_APPEND(head,id);
  }
  DL_FOREACH(head,elt) printf("%s", elt->bname);

  /* now delete each element, use the safe iterator */
  DL_FOREACH_SAFE(head,elt,tmp) {
    DL_DELETE(head,elt);
  }

  return 0;
}
