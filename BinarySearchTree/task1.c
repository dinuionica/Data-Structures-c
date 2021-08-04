
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

/* don't change this */
#define MAX_STRING_SIZE 49

char to_lower(char c)
{
    if ('A' <= c && c <= 'Z')
        return c + 0x20;
    return c;
}

int bst_cmp_str_lexicographically(const void *key1, const void *key2)
{
    int rc, i, len;
    char *str1 = (char *)key1;
    char *str2 = (char *)key2;
    int len1 = strlen(key1);
    int len2 = strlen(key2);

    len = len1 < len2 ? len1 : len2;
    for (i = 0; i < len; ++i) {
        rc = to_lower(str1[i]) - to_lower(str2[i]);

        if (rc == 0)
            continue;
        return rc;
    }

    rc = to_lower(str1[i]) - to_lower(str2[i]);
    return rc;
}

void print_data(void *data)
{
    printf("%s\n", (char*)data);
}

int main(void)
{
    bst_tree_t *bst;
    int N = 0, task;
    char str[BUFSIZ];

    scanf("%d", &N);
    fflush(stdout);

    bst = bst_tree_create(MAX_STRING_SIZE, bst_cmp_str_lexicographically);

    while (N--) {
        scanf("%d", &task);
        memset(str, 0, BUFSIZ);

        switch (task) {
        case 1:
            scanf("%s", str);
            bst_tree_insert(bst, str);
            break;
        case 2:
            scanf("%s", str);
            bst_tree_remove(bst, str);
            break;
        case 3:
            bst_tree_print_inorder(bst, print_data);
            break;
        default:
            perror("Invalid task!");
        }
    }

    bst_tree_free(bst, free);

    return 0;
}

/* 
========== Task 1
Test 1..........passed
Test 2..........passed
Test 3..........passed
Test 4..........passed
Test 5..........passed
=== Task Score: 35/35

5
1 abc
1 abcd
1 0a
1 0x
3
==77851== Memcheck, a memory error detector
==77851== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==77851== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==77851== Command: ./task1
==77851== 
0a
0x
abc
abcd
==77851== 
==77851== HEAP SUMMARY:
==77851==     in use at exit: 0 bytes in 0 blocks
==77851==   total heap usage: 11 allocs, 11 frees, 5,436 bytes allocated
==77851== 
==77851== All heap blocks were freed -- no leaks are possible
==77851== 
==77851== For lists of detected and suppressed errors, rerun with: -s
==77851== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/
