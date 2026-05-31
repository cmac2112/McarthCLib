#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

#include <stdio.h>

const char *ll_get_err_str(const ll_error_e err) {
    switch (err) {
        case LL_ERR_OK: return "OK";
            case LL_ERR_NOT_FOUND: return "Not Found";
            case LL_ERR_DATA_ALLOC: return "Allocating data";
            case LL_ERR_ENTRY_ALLOC: return "Allocating entry";
        default: return "Unknown";
    }
}
/* iterates through and free's all memory from all nodes sequentially */
static inline void free_all(ll_t *const ll) {
    struct ll_node *n = ll->head;
    struct ll_node *next = NULL;

    while (n != NULL) {
        if (!ll->byom) {
            free(n->data);
        }
        next = n->next;
        free(n);
        n = next;
    }
}

void *ll_search(ll_t *const ll, void *const data) {
    if (ll->match == NULL) return NULL;

    struct ll_node *n = ll->head;

    while (n != NULL) {
        if (ll->match(n->data, data)) return n-> data;
        n = n->next;
    }
    return NULL;
}

ll_error_e ll_insert(ll_t *const ll, void *const data) {
    struct ll_node *new = malloc(sizeof(struct ll_node));
    if (new == NULL) return LL_ERR_ENTRY_ALLOC;

    if (ll->byom) {
        new->data = data;
    } else {
        new->data = malloc(ll->d_size);

        if (new->data == NULL) {
            free(new);
            return LL_ERR_DATA_ALLOC;
        }

        memcpy(new->data, data, ll->d_size);
    }

    new->next = NULL;

    if (ll->head == NULL) {
        ll->head = new;
        ll->tail = new;
    } else {
        ll->tail->next = new;
        ll->tail = new;
    }

    ll->len++;
    return LL_ERR_OK;
}

ll_error_e ll_remove(ll_t *const ll, void *const data) {
    struct ll_node *n = ll->head;
    struct ll_node *prev = NULL;

    while (n != NULL) {
        if (ll->match(n->data, data)) {
            if (prev != NULL) {
                prev->next = n->next;
            } else {
                ll->head = n->next;
            }

            if (n == ll->tail) ll->tail = prev;
            if (!ll->byom) free(n->data);

            free(n);
            ll->len--;
            return LL_ERR_OK;
        }

        prev = n;
        n = n->next;
    }

    return LL_ERR_NOT_FOUND;
}

void ll_destroy(ll_t *const ll) {
    free_all(ll);
    memset(ll, 0x00, sizeof(ll_t));
}

void ll_init(ll_t *const ll, bool byom,
        size_t d_size, bool (*match)(void *const, void *const)) {
    ll->byom = byom;
    ll->len = 0;
    ll->d_size = d_size;
    if (match != NULL) {
        ll->match = match;
    }

    ll->head = NULL;
    ll->tail = NULL;
}

void ll_print_all_vals(ll_t *const ll) {
    int pos = 0;
    while (ll->head != NULL) {
        printf("pos %d: val: %d\n", pos, *(int *)ll->head->data);
        ll->head = ll->head->next;
        pos += 1;
    }
}