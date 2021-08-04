// Copyright 2021 Dinu Ion-Irinel

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

// swap function
void swap(int *number1, int *number2) {

    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

// bubble sort function
void bubble_sort(int size, int *array) {
    
    for (int i = 0; i < size - 1; ++i) {
        int swapped = 0;    
        for (int j = 0; j < size - 1 - i; ++j) {
            if (array[j] > array[j + 1]) {
                swap(&array[j], &array[j + 1]);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            return;
        }
    }
}

// simple sort function
void simple_sort(int size, int *array) {

    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size; ++j) {
            if (array[i] < array[j]) {
                swap(&array[i],&array[j]);
            }
        }   
    }
}

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

    // sort elements of array with bubble sort
    // bubble_sort(n, array);

    // sort elements of array with simple sort
    simple_sort(n, array);


    // display elements
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");

    // free memory of array
    free(array);
    return 0;
}

/*
gcc sort_functions.c && ./a.out 
5
11 2 3 900 14
*/
