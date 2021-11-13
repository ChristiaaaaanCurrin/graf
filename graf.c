
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

// main
int main () {
  list_t *list = malloc( sizeof( list_t ));
  *list = (list_t) { NULL };

  for ( v_t i = 0; i < 20; i++ ) {
    print_list( list );
    if ( i % 7 == 0 ) {
      behead( list );
    } else if ( i % 2 == 0 ) {
      add_first( list, i );
    } else {
      add_last( list, i );
    }
  }
  print_list( list );

  return 0;
}
