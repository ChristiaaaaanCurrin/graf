
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.h"

// main
int main () {
  printf( "%lu\n", sizeof( node_t ));
  printf( "%lu\n", sizeof( node_t* ));
  list_t *list = malloc( sizeof( list_t ));
  node_t *head = malloc( sizeof( node_t ));
  node_t *new_head = malloc( sizeof( node_t ));
  *head = (node_t) { 0, NULL };
  *list = (list_t) { head };

  print_list( list );
  //behead( list );
  add_last( list, 4 );
  print_list( list );
  add_last( list, 5 );
  print_list( list );
  add_first( list, 5 );
  *new_head = (node_t) { (*head).value, (*head).next };
  (*head).next = new_head;
  (*head).value = 5;
  print_list( list );

  return 0;
}
