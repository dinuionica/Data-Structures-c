#include <stdio.h>
#include "rb_tree.h"
#include "utils.h"

typedef struct team_t team_t;
struct team_t {
	char *name;
	int year;
};

static int
f(const void *key1, const void *key2)
{
	int a = *(int *)key1;
	int b = *(int *)key2;

	return (a < b ? -1 : (a == b) ? 0 : 1);
}

static void
rb_tree_free_data(void *data)
{
	free(((team_t *)data)->name);
}

static void
rb_tree_print_inorder(rb_node_t *root)
{
	if (root == NULL)
		return;

	rb_tree_print_inorder(root->left);
	printf("%d %s %d\n", *(int *)root->key, ((team_t *)root->data)->name,
		((team_t *)root->data)->year);
	rb_tree_print_inorder(root->right);
}

int
main(void)
{
	int N, task;
	int key;
	team_t *data;
	rb_tree_t *rb_tree = rb_tree_create(f, sizeof(int), sizeof(team_t));
	DIE(!rb_tree, "failed to create RB tree");

	scanf("%d\n", &N);
	while (N--) {
		scanf("%d\n", &task);

		if (task == 0) {
			data = malloc(sizeof(*data));
			DIE(!data, "failed to allocate data");

			data->name = calloc(BUFSIZ, sizeof(*data->name));
			DIE(!data->name, "failed to allocate data->name");

			scanf("%d %s %d\n", &key, data->name, &data->year);
			rb_tree_insert(rb_tree, &key, data);

			free(data);
		} else if (task == 1) {
			scanf("%d\n", &key);
			data = rb_tree_find(rb_tree, &key);
			if (data) {
				printf("%s %d\n", data->name, data->year);
				printf("%d\n", N);
			}
		}
	}

	rb_tree_print_inorder(rb_tree->root);

	rb_tree_free(rb_tree, NULL, rb_tree_free_data);
	free(rb_tree);

	return 0;
}

/* 
==191599== Memcheck, a memory error detector
==191599== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==191599== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==191599== Command: ./task2
==191599== 
asd 12
1
1 jkl 15
2 zxc 13
3 qwe 11
4 asd 12
5 iop 14
8 1337 8
99 bnm 0
==191599== 
==191599== HEAP SUMMARY:
==191599==     in use at exit: 0 bytes in 0 blocks
==191599==   total heap usage: 38 allocs, 38 frees, 63,084 bytes allocated
==191599== 
==191599== All heap blocks were freed -- no leaks are possible
==191599== 
==191599== For lists of detected and suppressed errors, rerun with: -s
==191599== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/