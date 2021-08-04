// Copyright 2021 Dinu Ion-Irinel

#include "binary_tree.h"

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

void print_data(void *data)
{
    printf("%d ", *(int *) data);
}

int main(void)
{
    b_tree_t *binary_tree = NULL;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);

    b_tree_print_preorder(binary_tree, print_data);
    b_tree_print_inorder(binary_tree, print_data);
    b_tree_print_postorder(binary_tree, print_data);

    my_free(binary_tree);

    return 0;
}

/* 
========== Task 1
Test 1..........passed
Test 2..........passed
Test 3..........passed
Test 4..........passed
=== Task Score: 40/40

========== Task 2
Test 1..........passed
Test 2..........passed
=== Task Score: 30/30

===== Total Score: 70/100

test for my_free 
valgrind --leak-check=full ./task1 < tests/in/task1/test2.in 
==347860== Memcheck, a memory error detector
==347860== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==347860== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==347860== Command: ./task1
==347860== 
71 40 80 73 86 21 18 99 54 98 
73 80 86 40 18 21 71 54 99 98 
73 86 80 18 21 40 54 98 99 71 
==347860== 
==347860== HEAP SUMMARY:
==347860==     in use at exit: 0 bytes in 0 blocks
==347860==   total heap usage: 86 allocs, 86 frees, 13,264 bytes allocated
==347860== 
==347860== All heap blocks were freed -- no leaks are possible
==347860== 
==347860== For lists of detected and suppressed errors, rerun with: -s
==347860== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/
