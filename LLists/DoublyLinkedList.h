#pragma once
#include <stddef.h>
#include <stdinit.h>
#include <stdbool.h>

/* define basic error types */
typedef enum{
  LL_ERR_OK,
  LL_ERR_NOT_FOUND,
  LL_ERR_ENTRY_ALLOC,
  LL_ERR_DATA_ALLOC,
} dll_error_e;

/*structure of a given node */
struct dll_node{
  void *data; //see void pointer, allows us to be type agnostic. Think of typeparams in C# kinda
  struct dll_node *next;
  struct dll_node *prev;
};

typedef struct{
  size_t len;
  size_t d_size;

  bool byom;
  bool (*match)(void *const, void *const);

  struct dll_node *head;
  struct dll_node *tail;
}dll_t;

//initialize a linked list
void dll_init(dll_t *const dll, bool byom, size_t d_size, bool (*match)(void *const, void *const));
//destroy ll and free memory
void dll_destroy(dll_t *const dll);

const char *dll_get_err_str(const dll_error_e err);

void *dll_search(dll_t *const dll, void *const data);
dll_error_e dll_insert(dll_t *const dll, void *const data);
// inserts after a given node
dll_error_e dll_insert_after(dll_t *const dll, void *const data, dll_node *const dll_n);
//inserts at a given index 
dll_error_e dll_insert_at(dll_t *const dll, void *const data, int pos);
