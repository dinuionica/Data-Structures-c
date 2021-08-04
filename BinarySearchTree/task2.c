
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "utils.h"

char to_lower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 0x20;
	return c;
}


int heap_cmp_str_lexicographically(const char *key1, const char *key2)
{
	int rc, i, len;

	len = strlen(key1) < strlen(key2) ? strlen(key1) : strlen(key2);
	for (i = 0; i < len; ++i) {
		rc = to_lower(key1[i]) - to_lower(key2[i]);

		if (rc == 0)
			continue;
		return rc;
	}

	rc = to_lower(key1[i]) - to_lower(key2[i]);
	return rc;
}


int heap_cmp_teams(const team_t *key1, const team_t *key2)
{
    int score_diff = key2->score - key1->score;

    if (score_diff != 0)
        return score_diff;

    return heap_cmp_str_lexicographically(key1->name, key2->name);
}

int main(void)
{
    heap_t *heap;
    team_t *team, *tmp_team;
    int N = 0, task;

    heap = heap_create(heap_cmp_teams);

    team = malloc(sizeof(*team));
    DIE(!team, "team malloc");
    team->name = malloc(BUFSIZ * sizeof(*team->name));
    DIE(!team->name, "team->name malloc");

    scanf("%d", &N);
    fflush(stdout);

    while (N--) {
        scanf("%d", &task);
    
        switch (task) {
        case 1:
            memset(team->name, 0, BUFSIZ);
            scanf("%s %d", team->name, &team->score);
            heap_insert(heap, team);
            break;
        case 2:
            if (!heap_empty(heap)) {
                tmp_team = heap_top(heap);
                printf("%s %d\n", tmp_team->name, tmp_team->score);
            }
            break;
        case 3:
            if (!heap_empty(heap)) {
                heap_pop(heap);
            }
            break;
        default:
            perror("Invalid task!");
        }
    }

    /* display score*/
    show_score(heap);

    free(team->name);
    free(team);
    heap_free(heap);

    return 0;
}

/* 
========== Task 2
Test 1..........passed
Test 2..........passed
Test 3..........passed
Test 4..........passed
Test 5..........passed
=== Task Score: 35/35

5
1 ax 1
1 b 3
1 a 5
1 z 3
1 0x 1
==110094== Memcheck, a memory error detector
==110094== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==110094== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==110094== Command: ./task2
==110094== 
a 5
b 3
z 3
0x 1
ax 1
==110094== 
==110094== HEAP SUMMARY:
==110094==     in use at exit: 0 bytes in 0 blocks
==110094==   total heap usage: 18 allocs, 18 frees, 13,694 bytes allocated
==110094== 
==110094== All heap blocks were freed -- no leaks are possible
==110094== 
==110094== For lists of detected and suppressed errors, rerun with: -s
==110094== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/
