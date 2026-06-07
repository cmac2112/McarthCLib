#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "LinkedList.h"


bool Search(void *const val1, void *const val2) {
    return *(int *)val1 == *(int *)val2;
}

//reverses a linked list and prints the result
int main() {
    ll_t ll;
    ll_error_e ll_err;

    ll_init(&ll, false, sizeof(int), NULL);

    int vals[] = {1, 2, 3, 5, 8, 13};

    for (int i = 0; i < sizeof(vals) / sizeof(int); i++) {
        if ((ll_err = ll_insert(&ll, &vals[i])) != LL_ERR_OK) {
            printf("ll_insert: %s\n", ll_get_err_str(ll_err));
            return 1;
        }
    }

    //reverse the values

    struct ll_node *cur = ll.head;
    struct ll_node *prev = NULL;
    struct ll_node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
        ll.tail = ll.head;
        ll.head = prev;
    ll_print_all_vals(&ll);
    /* free all, continue to next example */
    ll_destroy(&ll);

    return 0;

}