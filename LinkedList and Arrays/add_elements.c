//add elements into array

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

int main(int argc, char *argv[]) {

    //alloc memory of array
    int *array = malloc(SIZE * sizeof(int));
    
    if (array == NULL) {
        fprintf(stderr, "Error of malloc!\n");
        return -1;
    }

    int n;
    scanf("%d", &n);
    //read elements
    for (int i = 0; i < n; ++i) {
        scanf("%d", &array[i]);
    }

    //add elements
    for (int i = n - 1; i >= 0; --i) {
        if (array[i] % 2 == 0) {
            for (int j = n - 1; j >= i; --j) 
                array[j + 1] = array[j];
            n++;
            array[i + 1] = array[i] * 2;
        }
    }
    
    //display elements
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");

    //free memory of array
    free(array);
    return 0;
}

/*
gcc add_elements.c && ./a.out
5
1 2 3 4 5 */
