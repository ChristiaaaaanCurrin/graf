
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.c"
#include "graph.c"

// main
int main () {
  graph_t *g = cycle_graph( 10 );
  print_graph( g );
  return 0;
}
