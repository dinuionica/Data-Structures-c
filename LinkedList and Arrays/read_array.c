// Copyright 2021 Dinu Ion-Irinel

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[]) {

    // alloc memory of array
    int *array = malloc(SIZE * sizeof(int));
    
    if (array == NULL) {
        fprintf(stderr, "Error of malloc!\n");
        return -1;
    }

    int n;
    scanf("%d", &n);
    // read elements
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    // display elements
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");

    // free memory of array
    free(array);
    return 0;
}

/*gcc read_array.c && ./a.out
5
1 2 3 4 5 */
