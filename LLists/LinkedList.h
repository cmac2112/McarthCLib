#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* define basic error types */
typedef enum{
  LL_ERR_OK,
  LL_ERR_NOT_FOUND,
  LL_ERR_ENTRY_ALLOC,
  LL_ERR_DATA_ALLOC,
} ll_error_e;

/*structure of a given node */
struct ll_node{
  void *data; //see void pointer, allows us to be type agnostic. Think of typeparams in C# kinda
  struct ll_node *next;
};

struct ll_node_or_error {
  struct ll_node node;
  ll_error_e error;
};

typedef struct ll_node_or_error ll_node_or_error;

typedef struct{
  size_t len;
  size_t d_size;

  //byom: caller owns the data, we only store pointers
  //!byom: we malloc and memcpy each insert
  bool byom;
  bool (*match)(void *const, void *const);

  struct ll_node *head;
  struct ll_node *tail;
}ll_t;

//initialize a linked list
void ll_init(ll_t *const ll, bool byom, size_t d_size, bool (*match)(void *const, void *const));
//destroy ll and free memory
void ll_destroy(ll_t *const ll);
//gets error string of an ll_error_e enum
const char *ll_get_err_str(const ll_error_e err);
//searches for given data
void *ll_search(ll_t *const ll, void *const data);
ll_error_e ll_insert(ll_t *const ll, void *const data);
ll_error_e ll_remove(ll_t *const ll, void *const data);
void ll_print_all_vals(ll_t *const ll);

//searches the list at the given index
void *ll_retrive_node_at(ll_t *const ll, int index);

void *ll_retrive_midpoint(ll_t *const ll);

