#include <LinkedList.h>
#include <stdio.h>
#include <stdlib.h>

//initializes an example ll with a pointer to a vals array
ll_t initalizeExampleLL(int *const vals, int size) {
    ll_t ll;
    ll_error_e ll_err;


    //create our ll struct
    //we pass the memory address of our uninitialized ll here so ll_init modifies it rather than making a copy
    
    ll_init(&ll, true, sizeof(int), NULL);

    //add 10 digits of fib sequence to the ll

    for (int i = 0; i < size; i++) {
        if ((ll_err = ll_insert(&ll, &vals[i])) != LL_ERR_OK) {
            printf("ll_insert: %s\n", ll_get_err_str(ll_err));
            exit(1);
        }
    }
    return ll;
}


int main() {
    //find the midpoint of a given linked list

    //initialize our linked list with values from the args

    int arr[] = {0, 1, 1, 2, 3, 5, 7, 8, 13, 21, 34, 55};

    //when passing an array to a function, we are really just passing a pointer to its first element
    // this is why we need the size argument here of the typeof items divided by the size of the array to determine how long we should iterate inside of this function
    ll_t ll = initalizeExampleLL(arr, sizeof(arr) / sizeof(int));

    //create our fast pointer and regular pointer

    struct ll_node *fast = ll.head->next;
    struct ll_node *reg = ll.head;

    //iterate through the list until fast is at the end

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        reg = reg->next;
    }
    printf("midpoint for reg is %d\n", *(int *)reg->data);

    //4 line approach, returns mid+1 for double mid point lists

    struct ll_node *fast2 = ll.head;
    struct ll_node *reg2 = ll.head;

    while (fast2->next != NULL && fast2->next->next != NULL) {
        fast2 = fast2->next->next;
        reg2 = reg2->next;
    }
    printf("double midpoint + 1 for reg is %d\n", fast2->next != NULL ? *(int *)reg->next->data : *(int *)reg->data);


    ll_destroy(&ll);
    return 0;
}
