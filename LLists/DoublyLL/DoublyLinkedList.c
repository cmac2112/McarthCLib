#include <stdlib.h>
#include <string.h>
#include "DoublyLinkedList.h"

#include <stdio.h>

//return a pointer to the first char, the caller reads forward until they hit \0
const char *dll_get_err_str(const dll_error_e err) {
    switch (err) {
        case DLL_ERR_OK: return "OK";
        case DLL_ERR_NOT_FOUND: return "Not Found";
        case DLL_ERR_DATA_ALLOC: return "Allocating data";
        case DLL_ERR_ENTRY_ALLOC: return "Allocating entry";
        default: return "Unknown";
    }
}

//need to create a helper function to initialize a node
//need to assign an external pointer to this node

//if pointer points to a null data node we can return err

//solution is a pointer to a pointer,
dll_error_e init_node(struct dll_node **new_dll_ptr, dll_t *const dll, void *const data) {
    struct dll_node *new = malloc(sizeof(struct dll_node));
    if (new == NULL) return DLL_ERR_ENTRY_ALLOC;

    //if we "brought our own memory"
    if (dll->byom) {
        //just assign the data
        new->data = data;
    }else {
        //otherwize malloc new memory
        new->data = malloc(dll->d_size);
        if (new->data == NULL) {
            //if data allocation failed, free and return error
            free(new);
            return DLL_ERR_DATA_ALLOC;
        }
        //copy our data into the node
        memcpy(new->data, data, dll->d_size);
    }
    new->next =NULL;
    new->prev = NULL;
    *new_dll_ptr = new;
    return DLL_ERR_OK;
}

static inline void free_all_d(dll_t *const dll) {

    //create pointer to the head of the dll
    struct dll_node *n = dll->head;
    //placeholder pointer to the next dll node
    struct dll_node *next = NULL;

    //while our node is not null
    while (n != NULL) {
        //if we did not bring our own memory in initialization...
        if (!dll->byom) {
            //free the data in the node
            free(n->data);
        }
        // hold address of next
        next = n->next;
        // free current node
        free(n);
        //next address becomes our current
        n = next;
    }
}
void dll_init(dll_t *const dll, bool byom,
        size_t d_size, bool (*match)(void *const, void *const)) {
    dll->byom = byom;
    dll-> len = 0;
    if (match != NULL) {
        dll->match = match;
    }
    dll->head = NULL;
    dll->tail = NULL;
    dll->d_size = d_size;
}
dll_error_e dll_insert(dll_t *const dll, void *const data) {
    //malloc new memory size of the node
    struct dll_node *new = NULL;
    dll_error_e err = init_node(&new, dll, data);
    if (err != DLL_ERR_OK) return err;
    //setup our node pointers
    new->next = NULL;

    if (dll->head == NULL) {
        dll->head = new;
        dll->tail = new;
        new->prev = NULL;
    }else {
        dll->tail->next = new;
        new->prev = dll->tail;
        dll->tail = new;
    }
    dll-> len++;
    return DLL_ERR_OK;
}

//theres a way to do this with two pointers....

dll_error_e dll_remove(dll_t *const dll, void *const data) {
    //iterate through list, find data, remove
    struct dll_node *n = dll->head;
    struct dll_node *prev = NULL;

    //need to handle if this is the only node in the list,
    // check to see if its head or tail

    while (n != NULL) {
        if (dll->match(n->data, data)) {
            if (prev != NULL) {

                prev->next = n->next;
                if (n->next != NULL) n->next->prev = prev;

            }else {
                dll->head = n->next;
                if (dll->head != NULL) dll->head->prev = NULL;
            }
            //if our matched is tail, our new tail becomes prev
            if (n == dll->tail) dll->tail = prev;
            //free the data
            if (!dll->byom) free(n->data);

            free(n);
            dll->len--;
            return DLL_ERR_OK;
        }
        prev = n;
        n = n->next;
    }
    return DLL_ERR_NOT_FOUND;
}

dll_error_e dll_insert_after(dll_t *const dll, void *const data) {

    struct dll_node *n = dll->head;
    struct dll_node *prev = NULL;

    //similar to remove, itereate, find our match, insert after

    while (n != NULL) {
        if (dll->match(n->data, data)) {
            //insert after the data
            struct dll_node *new = malloc(sizeof(struct dll_node));
            if (new == NULL)
        }
    }



}

void dll_destroy(dll_t *const dll) {
    free_all_d(dll);
    memset(dll, 0x00, sizeof(dll_t));
}
void dll_print_all_vals(dll_t *const dll) {
    int pos = 0;
    //initialize a local pointer
    struct dll_node *n = dll->head;

    while (n != NULL) {
        printf("pos %d: val: %d\n", pos, *(int *)n->data);
        n = n->next;
        pos += 1;
    }
}

