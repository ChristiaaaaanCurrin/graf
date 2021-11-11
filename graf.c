#include <stdio.h>
#include <unistd.h>

// list definition
struct node {
  size_t value;
  struct node * next;
};

struct list {
  struct node * head;
};

// list queries
size_t length( struct list list ) {
  size_t len = 0;
  struct node *p = list.head;
  while (p != NULL) {
    p = (*p).next;
    len++;
  }
  return len;
}

struct node *first_node( struct list list ) {
  return list.head;
}

struct node* last_node( struct list list ) {
  struct node* node = list.head;
  while ((*node).next != NULL) {
    node = (*node).next;
  }
  return node;
}

size_t first( struct list list ) {
  return (*last_node( list )).value;
}

size_t last( struct list list ) {
  return (*first_node( list )).value;
}

// list modification
void insert_after( struct node *node, size_t value ) {
  struct node new_node = { value, (*node).next };
  (*node).next = &new_node;
}

void insert_before( struct node *node, size_t value ) {
  struct node new_node = { (*node).value, node };
  (*node).value = value;
}

void add_first( struct list *list, size_t value ) {
  insert_before( first_node( *list ), value );
}

void add_last( struct list *list, size_t value ) {
  insert_after( last_node( *list ), value );
}

void behead( struct list *list) {
  if ((*list).head != NULL) {
    (*list).head = (*(*list).head).next;
  }
}

void change_value( struct node *node, size_t value ) {
  (*node).value = value;
}

// list commands
void print_list( struct list list ) {
  printf("{ ");
  struct node * p = list.head;
  while (p != NULL) {
    printf( "%zu, ", (*p).value );
    p = (*p).next;
  }
  printf("\b\b }\n");
}

// main
int main () {
  struct node tail = { 5, NULL };
  struct node head = { 4, &tail };
  struct list list = { &head };

  print_list( list );

  add_first( &list, 3 );

  print_list( list );

  return 0;
}
