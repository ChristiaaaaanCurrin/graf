
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "list.c"
#include "graph.c"

// main
int main () {
  graph_t *g;
  printf( "--C20-----------------\n" );
  g = cycle_graph( 20 );
  print_graph( g );
  printf( "----------------------\n" );
  printf( "--P13-----------------\n" );
  g = path_graph( 13 );
  print_graph( g );
  printf( "----------------------\n" );
  printf( "--K4------------------\n" );
  g = complete_graph( 4 );
  print_graph( g );
  printf( "----------------------\n" );
  printf( "--E4------------------\n" );
  g = empty_graph( 4 );
  print_graph( g );
  printf( "----------------------\n" );
  return 0;
}
