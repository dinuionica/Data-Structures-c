#include <stdio.h>
#include <stdlib.h>
#include "avl.h"
#include "utils.h"

/**
 * Function that compares ints.
 * @return is similiar to that of strcmp.
 */
static int
cmp(const void* value1, const void* value2)
{

	int a = *(int*)value1; 
	int b = *(int*)value2;

	return (a < b ? -1 : (a == b) ? 0 : 1);
}

int
main(void)
{
	int task, no_inserts, no_deletes, no_finds, value, i;
	avl_tree_t *tree = avl_create(cmp);
	DIE(!tree, "failed to allocate tree");

	scanf("%d", &task);
	/* ------------- TASK 1 ------------- */
	if (task == 1)
		puts("------------- TASK 1 -------------");

	scanf("%d", &no_inserts);
	for (i = 0; i < no_inserts; ++i) {
		scanf("%d", &value);
		avl_insert(tree, &value, sizeof(value));

		/* Used for checker. */
		if (task == 1) {
			puts("Preoder");
			preorder_traversal(tree->root);
			printf("\n");
		}
	}

	if (task >= 2) {
		/* ------------- TASK 2 ------------- */
		if (task == 2)
			puts("------------- TASK 2 -------------");

		scanf("%d", &no_finds);
		for (i = 0; i < no_finds; ++i) {
			scanf("%d", &value);

			if (task == 3)
				continue;   

			if (get_key(tree, &value))
				printf("%d is in AVL.\n", value);
			else
				printf("%d is NOT in AVL.\n", value);
		}
	}

	/* ------------- TASK 4 ------------- */
	if (task == 3) {
		puts("------------- TASK 3 -------------");

		scanf("%d", &no_deletes);
		for (i = 0; i < no_deletes; ++i) {
			scanf("%d", &value);
			avl_delete(tree, &value);

			/* Used for checker. */
			puts("Preoder");
			preorder_traversal(tree->root);
			printf("\n");
		}
	}
	avl_free(tree);
	return 0;
}
/*
------------- TASK 1 -------------
Preoder
10 
Preoder
10 7 
Preoder
7 5 10 
Preoder
7 5 10 11 
Preoder
7 5 11 10 12 
==96493== 
==96493== HEAP SUMMARY:
==96493==     in use at exit: 0 bytes in 0 blocks
==96493==   total heap usage: 13 allocs, 13 frees, 5,316 bytes allocated
==96493== 
==96493== All heap blocks were freed -- no leaks are possible
==96493== 
==96493== For lists of detected and suppressed errors, rerun with: -s
==96493== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
------------- TASK 2 -------------
10 is in AVL.
6 is NOT in AVL.
12 is in AVL.
==97160== 
==97160== HEAP SUMMARY:
==97160==     in use at exit: 0 bytes in 0 blocks
==97160==   total heap usage: 13 allocs, 13 frees, 5,316 bytes allocated
==97160== 
==97160== All heap blocks were freed -- no leaks are possible
==97160== 
==97160== For lists of detected and suppressed errors, rerun with: -s
==97160== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
------------- TASK 3 -------------
Preoder
7 5 10 12 
Preoder
10 7 12 
Preoder
7 12 
==97166== 
==97166== HEAP SUMMARY:
==97166==     in use at exit: 0 bytes in 0 blocks
==97166==   total heap usage: 13 allocs, 13 frees, 5,316 bytes allocated
==97166== 
==97166== All heap blocks were freed -- no leaks are possible
==97166== 
==97166== For lists of detected and suppressed errors, rerun with: -s
==97166== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0) */