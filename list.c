
typedef void *v_t;

// list definition

typedef struct node {
  v_t value;
  struct node *next;
} node_t;

typedef struct list {
  struct node *head;
  struct node *tail;
} list_t;

// error behavior
void empty_list_error() {
 // printf( "EMPTY LIST ERROR\n"  );
}

// list commands
void print_list( list_t *list ) {
  printf("{");
  if ( (*list).head == NULL ) {
    printf( "}\n" );
  } else {
    node_t *p = (*list).head;
    while (p != NULL) {
      printf( " %x,", 0xff & ((int) (*p).value >> 3) );
      p = (*p).next;
    }
    printf("\b }\n");
  }
}

list_t *new_list() {
  list_t *list = malloc( sizeof( list_t ) );
  *list = (list_t) { NULL, NULL };
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
  return (*list).tail;
}

v_t first( list_t *list ) {
  if ( (*list).head != NULL ) {
    return (*(*list).head).value;
  } else {
    empty_list_error();
    return NULL;
  }  
}

v_t last( list_t *list ) {
  if ( (*list).tail != NULL ) {
    return (*(*list).tail).value;
  } else {
    empty_list_error();
    return NULL;
  }  
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
void add_first( list_t *list, v_t value ) {
  node_t *node = malloc( sizeof( node_t ) );
  *node = (node_t) { value, (*list).head };

  if ( (*list).head == NULL ) {
    (*list).tail = node;
  }
  (*list).head = node;
}

void add_last( list_t *list, v_t value ) {
  node_t *node = malloc( sizeof( node_t ) );
  *node = (node_t) { value, NULL };
  if ( (*list).head == NULL ) {
    (*list).head = node;
  } else {
    (*(*list).tail).next = node;
    (*list).tail = node;
  }
}

v_t take_first( list_t *list ) {
  if ( (*list).head != NULL ) {
    node_t *p = (*list).head;
    (*list).head = (*p).next;
    v_t v = (*p).value;
    free( p );
    return v;
  } else {
    empty_list_error();
    return NULL;
  }
}

v_t take_last( list_t *list ) {
  if ( (*list).tail != NULL ) {
    node_t *p = (*list).tail;
    v_t v = (*p).value;
    free( p );
    node_t *q = (*list).head;
    while ( (*q).next != NULL ) {
    q = (*q).next;
    }
    (*list).tail = q;
    return v;
  } else {
    empty_list_error();
    return NULL;
  }
}

void remove_all( list_t *list, v_t v ) { // warning: this method violates the order of the list!
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( (*p).value == v ) {
      (*p).value = first( list );
      take_first( list );
    }
    p = (*p).next;
  }
}

void remove_one( list_t *list, v_t v ) { // warning:this method violates the order of the list!
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( (*p).value == v ) {
      (*p).value = first( list );
      take_first( list );
      return;
    }
    p = (*p).next;
  }
}

void clear_list( list_t *list ) {
  while ( (*list).head != NULL ) {
    take_first( list );
  }
}

void kill_list( list_t *list ) {
  clear_list( list );
  free( list );
}

list_t *copy_list( list_t* list ) {
  list_t *list2 = new_list();
  node_t *p = (*list).head;
  while ( p != NULL ) {
    add_last( list2, (*p).value );
    p = (*p).next;
  }
  return list2;
}

void map( void *f( v_t ), list_t *list ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    f( (*p).value );
    p = (*p).next;
  }
}

int any( int *f( v_t ), list_t *list ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( f( (*p).value ) ) {
      return 1;
    }
    p = (*p).next;
  }
  return 0;
}

int all( int *f( v_t ), list_t *list ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( !f( (*p).value ) ) {
      return 0;
    }
    p = (*p).next;
  }
  return 1;
}

int contains( v_t v, list_t * list ) {
  node_t *p = (*list).head;
  while ( p != NULL ) {
    if ( v == (*p).value ) {
      return 1;
    }
  }
  return 0;
}

void concat( list_t *list1, list_t * list2 ) {
  node_t *p = (*list1).head;
  while ( p != NULL ) {
    add_last( list1, (*p).value );
    p = (*p).next;
  }
}

int is_Empty( list_t *list) {
  return (*list).head == NULL;
}
