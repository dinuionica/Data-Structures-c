/* Copyright 2021 Dinu Ion-Irinel */

#include "heap.h"
#include "utils.h"

heap_t *heap_create(int (*cmp_f)(const team_t *, const team_t *))
{
    heap_t *heap;

    heap = malloc(sizeof(*heap));
    DIE(heap == NULL, "heap malloc");

    heap->cmp = cmp_f;
    heap->size = 0;
    heap->capacity = 2;
    heap->arr = malloc(heap->capacity * sizeof(*heap->arr));
    DIE(heap->arr == NULL, "heap->arr malloc");

    return heap;
}

static void __heap_insert_fix (heap_t * heap, int pos)
{
     int parent = GO_UP (pos);

     while (pos> 0 && heap-> arr [parent] -> score <heap-> arr [pos] -> score)
     {
         // exchange the value with the value of the parent
         team_t * tmp_team = heap-> arr [parent];
         heap-> arr [parent] = heap-> arr [pos];
         heap-> arr [pos] = tmp_team;
     }

     // update the new parent
     pos = parent;
     parent = GO_UP (pos);
}

void heap_insert(heap_t *heap, team_t *team)
{
    char *rc;

    heap->arr[heap->size] = malloc(sizeof(**heap->arr));
    DIE(heap->arr[heap->size] == NULL, "heap_insert malloc");

    heap->arr[heap->size]->name = calloc(TEAM_NAME_LEN,
                                         sizeof(*heap->arr[heap->size]->name));
    DIE(heap->arr[heap->size]->name == NULL, "heap_insert name calloc");

    rc = strncpy(heap->arr[heap->size]->name, team->name,
                 TEAM_NAME_LEN - 1);
    DIE(rc != heap->arr[heap->size]->name, "heap_insert name strncpy");
    heap->arr[heap->size]->score = team->score;

    __heap_insert_fix(heap, heap->size);

    heap->size++;
    if (heap->size == heap->capacity)
    {
        heap->capacity *= 2;

        heap->arr = realloc(heap->arr,
                            heap->capacity * sizeof(*heap->arr));
        DIE(heap->arr == NULL, "heap->arr realloc");
    }
}

team_t *heap_top(heap_t *heap)
{
    // retur root
    return heap->arr[0];
}

static void __heap_pop_fix (heap_t * heap, int pos)
{

     int p = pos;
     int l = GO_LEFT (pos);
     int r = GO_RIGHT (pos);

     // if the shaft limit is exceeded
     if (r> = heap-> size || l> = heap-> size)
     {
         return;
     }
     // if the tree does not contain the correct order
     if (heap-> cmp (heap-> arr [p], heap-> arr [l]) <0 ||
         heap-> cmp (heap-> arr [p], heap-> arr [r]) <0)
     {
         // I exchange the parent with the eldest son
         if (heap-> cmp (heap-> arr [l], heap-> arr [r]) <0)
         {
             // right son
             team_t * tmp_team = heap-> arr [p];
             heap-> arr [p] = heap-> arr [r];
             heap-> arr [r] = tmp_team;
             pos = r;
         }
         else
         {
             // left son
             team_t * tmp_team = heap-> arr [p];
             heap-> arr [p] = heap-> arr [l];
             heap-> arr [l] = tmp_team;
             pos = l;
         }
         __heap_pop_fix (heap, pos);
     }
     return;
}
void heap_pop(heap_t *heap)
{
    free(heap->arr[0]->name);
    free(heap->arr[0]);

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    __heap_pop_fix(heap, 0);
}

int heap_empty(heap_t *heap)
{
    return heap->size <= 0;
}

void heap_free (heap_t * heap)
{
     // I go through the heap and release the memory
     for (int i = 0; i <heap-> size; ++ i)
     {
         free (heap-> arr [i] -> name);
         free (heap-> arr [i]);
     }
     free (heap-> arr);
     free (heap);
     heap = NULL;
}

team_t * get_first_score (heap_t * heap, int * pos)
{
     * pos = 0;
     int max_score = heap-> arr [0] -> score;

     // I'm looking for the team with the highest score
     for (int i = 0; i <heap-> size; ++ i)
     {
         if (heap-> arr [i] -> score> = max_score)
         {
             * pos = i;
             max_score = heap-> arr [i] -> score;
         }
     }
     // get the position, sorted by name
     for (int i = 0; i <heap-> size; ++ i)
     {
         if (heap-> arr [i] -> score == max_score)
         {
             if (heap_cmp_str_lexicographically (heap-> arr [i] -> name,
                 heap-> arr [* pos] -> name) <0)
             {
                 * pos = i;
             }
         }
     }

     return heap-> arr [* pos];
}
void remove_team (heap_t * heap, int pos)
{
     // release the memory allocated to the team
     free (heap-> arr [pos] -> name);
     heap-> arr [pos] -> name = NULL;
     free (heap-> arr [pos]);
     heap-> arr [pos] = NULL;

     // move each element in the vector one position to the right
     for (int i = pos; i <heap-> size - 1; ++ i)
     {
         heap-> arr [i] = heap-> arr [i + 1];
     }
     // update the size
     heap-> size--;
}

void show_score (heap_t * heap)
{
     int heap_size = heap-> size;
     for (int i = 0; i <heap_size; ++ i)
     {
         int pos = 0;
         // I get the team with the maximum score and I display it
         team_t * tmp = get_first_score (heap, & pos);
         printf ("% s% d \ n", tmp-> name, tmp-> score);
         // delete the team
         remove_team (heap, pos);
     }
}
