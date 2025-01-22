#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include "list.h" 

int main() {
    List_T myList = NULL;

    myList = List_push(myList, (void *)(intptr_t)3);
    myList = List_push(myList, (void *)(intptr_t)2);
    myList = List_push(myList, (void *)(intptr_t)1);

    for (List_T current = myList; current != NULL; current = current->rest) {
        printf("%d ", (int)(intptr_t)(current->first));
    }
    printf("\n");

    //1 2 3
    List_free(&myList);

    return 0;
}
