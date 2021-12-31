
// graph definition
typedef struct edge {
  list_t *incidents;
} edge_t;

typedef struct igraph {
  list_t *edge_set;
} igraph_t;

// graph queries
list_t *neighborhood( vertex_t *v ) {
  return (*v).neighborhood;
}

list_t *in_neighborhood( vertex_t *v ) {
  return (*v).in_neighborhood;
}

size_t order( graph_t *g ) {
  return length( (*g).vertex_set );
}

list_t *vertex_set( graph_t *g ) {
  return (*g).vertex_set;
}

size_t degree( vertex_t *v ) {
  return length( neighborhood( v ) );
}

size_t in_degree( vertex_t *v ) {
  return length( in_neighborhood( v ) );
}

int adjacent( vertex_t *v, vertex_t *u ) {
  return 0 <= list_index( neighborhood( v ), u );
}

// graph modification
void link_m( vertex_t *v, vertex_t *u ) {
  add_first(    neighborhood( v ), u );
  add_first( in_neighborhood( u ), v );
}

void link_d( vertex_t *v, vertex_t *u ) {
  if (!adjacent( v, u ) ) {
    add_first(    neighborhood( v ), u );
    add_first( in_neighborhood( u ), v );
  }
}

void link_u( vertex_t *v, vertex_t *u ) {
  if (!adjacent( v, u ) ) {
    add_first(    neighborhood( v ), u );
    add_first( in_neighborhood( u ), v );
  }
  if (!adjacent( u, v ) ) {
    add_first(    neighborhood( u ), v );
    add_first( in_neighborhood( v ), u );
  }
}

void loop_m( vertex_t *v ) {
  link_m( v, v );
}

void loop_d( vertex_t *v ) {
  link_d( v, v );
}

void loop_u( vertex_t *v ) {
  link_u( v, v );
}

void unlink_m( vertex_t *v, vertex_t *u ) {
  remove_one(    neighborhood( v ), u );
  remove_one( in_neighborhood( u ), v );
}

void unlink_d( vertex_t *v, vertex_t *u ) {
  remove_all(    neighborhood( v ), u );
  remove_all( in_neighborhood( u ), v );
}

void unlink_u( vertex_t *v, vertex_t *u ) {
  remove_all(    neighborhood( v ), u );
  remove_all( in_neighborhood( u ), v );
  remove_all(    neighborhood( u ), v );
  remove_all( in_neighborhood( v ), u );
}

void clear_vertex( vertex_t *v ) {
  node_t *p = (*neighborhood( v )).head;
  while ( p != NULL ) {
    unlink_u( v, (*p).value );
    p = (*p).next;
  }
}

void delete_vertex( graph_t *g, vertex_t *v ) {
  clear_vertex( v );
  remove_all( (*g).vertex_set, v );
  free( neighborhood( v ) );
  free( in_neighborhood( v ) );
  free( v );
}

// graph commands
void print_graph( graph_t *g ) {
  node_t *p = first_node( (*g).vertex_set );
  while ( p != NULL ) {
    printf( "%x\t", 0xff & ((int) (*p).value >> 3) );
    print_list( neighborhood( (*p).value ) );
    p = (*p).next;
  }
}

vertex_t *empty_vertex(){
  vertex_t *v = malloc( sizeof( vertex_t ) );
  *v = (vertex_t) { new_list(), new_list() };
  return v;
}

vertex_t *copy_vertex( vertex_t *v ) {
  vertex_t *u = malloc( sizeof( vertex_t ) );
  *u = (vertex_t) { copy_list( neighborhood( v ) ), copy_list( in_neighborhood( v ) ) };
  return u;
}

graph_t *empty_graph( size_t order ) {
  graph_t *g = malloc( sizeof( graph_t ) );
  list_t *vs = new_list();
  for (int i = 0; i < order; i++ ) {
    add_first( vs, empty_vertex() );
  }
  *g = (graph_t) { vs };
  return g;
}

graph_t *path_graph( size_t order ) {
  graph_t *g = empty_graph( order );
  node_t *p = first_node( (*g).vertex_set );
  node_t *q;
  while ( p != NULL ) {
    q = (*p).next;
    if ( q != NULL ) {
      link_u( (*p).value, (*q).value );
    }
    p = (*p).next;
  }
  return g;
}

graph_t *cycle_graph( size_t order ) {
  graph_t *g = path_graph( order );
  link_u( first( (*g).vertex_set ), last( (*g).vertex_set ) );
  return g;
}

graph_t *complete_graph( size_t order ) {
  graph_t *g = empty_graph( order );
  node_t *p = first_node( (*g).vertex_set );
  node_t *q;
  while ( p != NULL ) {
    q = (*p).next;
    while ( q != NULL ) {
      link_u( (*p).value, (*q).value );
      q = (*q).next;
    }
    p = (*p).next;
  }
  return g;
}

int distance( vertex_t *v, vertex_t *u ) {
  
  return -1;
}

