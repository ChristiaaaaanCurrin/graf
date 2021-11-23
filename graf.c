
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// list definition
typedef size_t v_t;

typedef struct node {
  v_t value;
  struct node * next;
} node_t;

typedef struct list {
  struct node * head;
} list_t;

// list commands
void print_list( list_t *list ) {
  printf("{");
  if ( (*list).head == NULL ) {
    printf( "}\n" );
  } else {
    node_t * p = (*list).head;
    while (p != NULL) {
      printf( " %zu,", (*p).value );
      p = (*p).next;
    }
    printf("\b }\n");
  }
}

list_t *new_list() {
  list_t *list = malloc( sizeof( list_t ) );
  *list = (list_t) { NULL };
  return list;
}

// list queries
size_t length( list_t *list ) {
  size_t len = 0;
  node_t *p = (*list).head;
  while (p != NULL) {
    p = (*p).next;
    len++;
  }
  return len;
}

node_t *first_node( list_t *list ) {
  return (*list).head;
}

node_t *last_node( list_t *list ) {
  node_t *node = (*list).head;
  if ( node == NULL ) {
    return node;
  }
  while ( (*node).next != NULL ) {
    node = (*node).next;
  }
  return node;
}

v_t first( list_t *list ) {
  return (*first_node( list )).value;
}

v_t last( list_t *list ) {
  return (*last_node( list )).value;
}

int list_index( list_t *list, v_t v ) {
  node_t *p = (*list).head;
  for (int i = 0; p != NULL; i++) {
    if ( (*p).value == v ) {
      return i;
    }
    p = (*p).next;
  }
  return -1;
}

// list modification
void insert_after( node_t *node, v_t value ) {
  node_t *new_node = malloc( sizeof( node_t ) );

  *new_node = (node_t) { value, (*node).next };
  (*node).next = new_node;
}

void insert_before( node_t *node, v_t value ) {
  node_t *new_node = malloc( sizeof( node_t ) );

  *new_node = (node_t) { (*node).value, (*node).next };
  *node = (node_t) { value, new_node };
}

void add_first( list_t *list, v_t value ) {
  node_t *node = malloc( sizeof( node_t ) );

  *node = (node_t) { value, (*list).head };
  (*list).head = node;
}

void add_last( list_t *list, v_t value ) {
  node_t *node = last_node( list );
  if ( node == NULL ) {
    add_first( list, value );
  } else {
    insert_after( node, value );
  }
}

void behead( list_t *list) {
  if ( (*list).head != NULL ) {
    node_t *p = (*list).head;
    (*list).head = (*p).next;
    free( p );
  }
}

void set_value( node_t *node, v_t value ) {
  (*node).value = value;
}

void remove_all( list_t *list, v_t v ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( (*p).value == v ) {
      (*p).value = first( list );
      behead( list );
    }
    p = (*p).next;
  }
}

void remove_one( list_t *list, v_t v ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( (*p).value == v ) {
      (*p).value = first( list );
      behead( list );
      return;
    }
    p = (*p).next;
  }
}

// graph definition
typedef struct graph {
  size_t max_order;
  size_t order;
  list_t (*vertex_set)[];
} graph_t;

// graph queries
list_t *neighborhood( graph_t *g, v_t i ) {
  return &(*(*g).vertex_set)[i];
}

size_t degree( graph_t *g, v_t i ) {
  return length( neighborhood( g, i ) );
}

int adjacent( graph_t *g, v_t i, v_t j ) {
  return 0 <= list_index( neighborhood( g, i ), j );
}

// graph modification
void link_m( graph_t *g, v_t i, v_t j ) {
  add_first( neighborhood( g, i ), j );
}

void link_d( graph_t *g, v_t i, v_t j ) {
  if (!adjacent( g, i, j ) ) {
    add_first( neighborhood( g, i ), j );
  }
}

void link_u( graph_t *g, v_t i, v_t j ) {
  if (!adjacent( g, i, j ) ) {
    add_first( neighborhood( g, i ), j );
    add_first( neighborhood( g, j ), i );
  }
}

void unlink_m( graph_t *g, v_t i, v_t j ) {
  remove_one( neighborhood( g, i ), j );
}

void unlink_d( graph_t *g, v_t i, v_t j ) {
  remove_all( neighborhood( g, i ), j );
}

void unlink_u( graph_t *g, v_t i, v_t j ) {
  remove_all( neighborhood( g, i ), j );
  remove_all( neighborhood( g, j ), i );
}

// graph commands
void print_graph( graph_t *g ) {
  for ( int i = 0; i < (*g).order; i++ ) {
    printf( "%d ", i );
    print_list( &(*(*g).vertex_set)[i] );
  }
}

graph_t *empty_graph( size_t order ) {
  list_t (*vs)[order] = calloc( sizeof( list_t ), 2 * order );
  graph_t *g = malloc( 2 * sizeof( size_t ) + 2 * sizeof( list_t ) );
  *g = (graph_t) { 2 * order, order, vs };
  return g;
}

graph_t *complete_graph( size_t order ) {
  graph_t *g = empty_graph( order );
  for ( v_t i = 0; i < order; i++ ) {
    for ( v_t j = 0; j < i; j++ ) {
      link_u( g, i, j );
    }
  }
  return g;
}

graph_t *path_graph( size_t order ) {
  graph_t *g = empty_graph( order );
  for ( v_t i = 1; i < order; i++ ) {
    link_u( g, i - 1, i );
  }
  return g;
}

graph_t *cycle_graph( size_t order ) {
  graph_t *g = path_graph( order );
  if ( 1 < order ) {
    link_u( g, 0, order - 1 );
  }
  return g;
}

// main
int main () {
  graph_t *g = cycle_graph( 10 );
  print_graph( g );
  return 0;
}
