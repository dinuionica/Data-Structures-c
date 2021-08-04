// Copyright 2021 Dinu Ion-Irinel
#include <stdio.h>

int binary_search(int number, int *array, int left, int right) {

    while (left <= right) {
        int mid = (left + right) / 2;

        // if the element is middle
        if (array[mid] == number) {
            return 1;
        } else if (array[mid] < number) {
            return binary_search(number, array, mid + 1, right);
        } else {
            return binary_search(number, array, left, mid - 1);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {

    int array[] = {1,2,3,4,5,6};
    int size = 6;
    int number;
    scanf("%d", &number);
    
    if (binary_search(number, array, 0, size - 1) == 1) {

        printf("True\n");
    } else {

        printf("False\n");
    }
    return 0;
}
