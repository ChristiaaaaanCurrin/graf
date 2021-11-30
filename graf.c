
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.c"
#include "graph.c"

// main
int main () {
  graph_t *g = empty_graph( 10 );
  print_graph( g );
  link_u( first( vertex_set( g ) ), last( vertex_set( g ) ) ); 
  print_graph( g );
  return 0;
}
