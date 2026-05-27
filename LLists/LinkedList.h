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

void ll_init(ll_t *const ll, bool byom, size_t d_size, bool (*match)(void *const, void *const));

void ll_destroy(ll_t *const ll);

const char *ll_get_err_str(const ll_error_e err);

void *ll_search(ll_t *const ll, void *const data);
ll_error_e ll_insert(ll_t *const ll, void *const data);
ll_error_e ll_remove(ll_t *const ll, void *const data);

