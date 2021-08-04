// Copyright 2021 Dinu Ion-Irinel

#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int *interclassing(int *array1, int size1, int *array2, int size2) {

      // final array
    int *array3 =(int *) malloc(2 * SIZE * sizeof(int));

    if (array3 == NULL) {
        fprintf(stderr, "Error of malloc!\n");
        return NULL;
    }

    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (array1[i] < array2[j]) {
            array3[k++] = array1[i++];
        } else {
            array3[k++] = array2[j++];
        }
    }

    while (i < size1) {
        array3[k++] = array1[i++];
    }

    while (j < size2) {
        array3[k++] = array2[j++];
    }
    
    return array3;
}

int main(int argc, char *argv[]) {

    int *array1 = (int *) malloc(SIZE * sizeof(int));

    if (array1 == NULL) {
        fprintf(stderr, "Error of malloc!\n");
        return -1;
    }

    int *array2 =(int *) malloc(SIZE * sizeof(int));

    if (array2 == NULL) {
        fprintf(stderr, "Error of malloc!\n");
        return -1;
    }

    // read elements
    int size1, size2;
    scanf("%d", &size1);

    for (int i = 0; i < size1; ++i) {
        scanf("%d", &array1[i]);
    }
    scanf("%d", &size2);

    for (int i = 0; i < size2; ++i) {
        scanf("%d", &array2[i]);
    }


    // interclassing
    int *array3 =(int *) interclassing(array1, size1, array2, size2);

    // display elements

    for (int i = 0; i < (size1 + size2); ++i) {
        printf("%d ", array3[i]);
    }

    free(array1);
    free(array2);
    free(array3);
    
    return 0;
}
