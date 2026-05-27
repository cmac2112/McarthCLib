#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
/*adds integers to a ll and prints them sequentially */
/* this ll supports generic types but ints will do for now */
bool Search(void *const val1, void *const val2) {
    return *(int *)val1 == *(int *)val2;
}

void PrintAllValues(ll_t *const ll) {
    int pos = 0;
    while (ll->head != NULL) {
        printf("pos %d: val: %d\n", pos, *(int *)ll->head->data);
        ll->head = ll->head->next;
        pos += 1;
    }
}

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

    /* print all the values */
    PrintAllValues(&ll);

    /* free all, continue to next example */
    ll_destroy(&ll);

    /* ------------------Searching And Removing---------------------------- */

    ll_t sll;

    ll_init(&sll, false, sizeof(int), Search);

    for (int i = 0; i < sizeof(vals) / sizeof(int); i++) {
        if ((ll_err = ll_insert(&sll, &vals[i])) != LL_ERR_OK) {
            printf("ll_insert: %s\n", ll_get_err_str(ll_err));
            return 1;
        }
    }

    /* ---------- contains value --------- */
    void *result = ll_search(&sll, &vals[3]);
    if (result != NULL) {
        printf("value found!\n");

    }else {
        printf("value not found\n");
    }

    /* ---------- does not contain value --------- */

    int searchval = 21;
    void *secondResult = ll_search(&sll, &searchval);
    if (secondResult != NULL) {
        printf("value found!\n");

    }else {
        printf("value not found\n");
    }


    /* ---------- removes present item ----------- */

if ((ll_err = ll_remove(&sll, &vals[3]) == LL_ERR_NOT_FOUND)){
    printf("failed to remove %d\n", vals[3]);
    return 1;
}else {
    printf("value removed succesfully \n");
    PrintAllValues(&sll);
}
    return 0;
}

