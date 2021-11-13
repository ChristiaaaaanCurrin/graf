
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
  while ((*node).next != NULL) {
    node = (*node).next;
  }
  return node;
}

v_t first( list_t *list ) {
  return (*last_node( list )).value;
}

v_t last( list_t *list ) {
  return (*first_node( list )).value;
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
    free(p);
  }
}

void set_value( node_t *node, v_t value ) {
  (*node).value = value;
}

