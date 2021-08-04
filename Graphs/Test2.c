// Copyright 2021 Dinu Ion-Irinel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"

#define MAX_NODES 100
#define INF 0x3f3f3f3f

enum color
{
	WHITE,
	BLACK,
	GRAY
};


static void
dfs_connected_comps(
	list_graph_t *lg,
	int node,
	int *visited,
	linked_list_t *component)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	// create stack
	stack_t *stack = st_create(sizeof(int));
	// add first node and mark as visited
	visited[node] = GRAY;
	st_push(stack, &node);
	ll_add_nth_node(component, component->size, &node);

	while (!st_is_empty(stack))
	{
		// take the top
		int top = *(int *)st_peek(stack);
		int node_found = 0;
		int v = 0, i = 0;
		ll_node_t *node = lg->neighbors[top]->head;
		// find unvisited neighbours
		while (node != NULL)
		{
			v = *(int *)node->data;
			if (visited[v] == WHITE)
			{
				node_found = 1;
				break;
			}
			node = node->next;
		}
		// add the neighbour in stack
		if (node_found == 1)
		{
			visited[v] = GRAY;
			st_push(stack, &v);
			ll_add_nth_node(component, component->size, &v);
		}
		else
		{
			// remove from the stack
			visited[top] = BLACK;
			st_pop(stack);
		}
	}
	// free memory
	st_clear(stack);
	st_free(stack);
}

static linked_list_t **
connected_components(list_graph_t *lg, int *visited, unsigned int *num_comp)
{
	linked_list_t **comps = malloc(lg->nodes * sizeof(*comps));
	DIE(!comps, "malloc comps failed");

	for (int i = 0; i < lg->nodes; ++i)
	{
		comps[i] = ll_create(sizeof(int));
	}
	enum color;
	if (lg == NULL)
	{
		return NULL;
	}
	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		visited[i] = WHITE;
	}

	for (int i = 0; i < lg->nodes; ++i)
	{
		if (visited[i] == WHITE)
		{
			dfs_connected_comps(lg, i, visited, comps[*num_comp]);
			*num_comp = *num_comp + 1;
		}
	}

	return comps;
}

static void
min_path(list_graph_t *lg, int node, int *dist)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	int color[MAX_NODES];
	for (int i = 0; i < lg->nodes; ++i)
	{
		color[i] = WHITE;
	}
	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		color[i] = WHITE;
		dist[i] = INF;
	}

	queue_t *queue = q_create(sizeof(int), MAX_NODES);
	// add first node
	printf("%d ", node);
	q_enqueue(queue, &node);
	dist[node] = 0;
	color[node] = GRAY;

	while (q_is_empty(queue) == 0)
	{
		// take the first elemnt from queue
		int top = *(int *)q_front(queue);
		q_dequeue(queue);

		// find visited neighbours
		ll_node_t *current = lg->neighbors[top]->head;
		while (current != NULL)
		{
			int v = *(int *)current->data;
			// if I find an unvisited one I add it in the queue
			if (color[v] == WHITE)
			{
				printf("%d ", v);
				color[v] = GRAY;
				dist[v] = dist[top] + 1;
				q_enqueue(queue, &v);
			}
			current = current->next;
		}
		// mark the extracted node
		color[top] = BLACK;
	}
	// free memory
	q_clear(queue);
	q_free(queue);
}

static int
check_bipartite(list_graph_t *lg, int *color)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	int level[MAX_NODES];
	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		color[i] = WHITE;
		level[i] = 0;
	}

	queue_t *queue = q_create(sizeof(int), MAX_NODES);
	// add the first node
	int node = 0;
	printf("%d ", node);
	q_enqueue(queue, &node);
	color[node] = GRAY;
	level[node] = 1; // set level

	while (q_is_empty(queue) == 0)
	{
		// access and remove the first node from the queue
		int top = *(int *)q_front(queue);
		q_dequeue(queue);

		// find unvisited neighbours
		ll_node_t *current = lg->neighbors[top]->head;
		while (current != NULL)
		{
			int v = *(int *)current->data;
			// update the level
			if (level[v] == 0)
			{	
				if (level[top] == 1)
				{
					level[v] = 2;
				}
				else
				{
					level[v] = 1;
				}
				color[v] = GRAY;
				q_enqueue(queue, &v);
			}
			else
			{
				// if both have the same level the graph is not bipartite
				if (level[top] == level[v])
				{
					q_clear(queue);
					q_free(queue);
					return 0;
				}
			}
			current = current->next;
		}
		// mark the node S
		color[top] = BLACK;
	}
	// free memory
	q_clear(queue);
	q_free(queue);
	// the graph is bipartite
	return 1;
}

void dfs_topo_sort(list_graph_t *lg, int node, int *visited, linked_list_t *sorted)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	// create the stack
	stack_t *stack = st_create(sizeof(int));
	// add the first node and mark it 
	visited[node] = GRAY;
	st_push(stack, &node);

	while (!st_is_empty(stack))
	{
		// take the top of the stack
		int top = *(int *)st_peek(stack);
		int node_found = 0;
		int v = 0;
		ll_node_t *node = lg->neighbors[top]->head;
		// // find unvisited neighbours
		while (node != NULL)
		{
			v = *(int *)node->data;
			if (visited[v] == WHITE)
			{
				node_found = 1;
				break;
			}
			node = node->next;
		}
		// if I found a neighbor I add it to the stack and mark it
		if (node_found == 1)
		{
			visited[v] = GRAY;
			st_push(stack, &v);
		}
		else
		{
			// if I don't add it to the list, I make it black and delete it
			ll_add_nth_node(sorted, 0, &top);
			visited[top] = BLACK;
			st_pop(stack);
		}
	}
	// free memory
	st_clear(stack);
	st_free(stack);
}

static linked_list_t *
topo_sort(list_graph_t *lg, int *visited)
{
	linked_list_t *sorted = ll_create(sizeof(int));

	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		visited[i] = WHITE;
	}

	for (int i = 0; i < lg->nodes; ++i)
	{
		if (visited[i] == WHITE)
		{
			dfs_topo_sort(lg, i, visited, sorted);
		}
	}

	return sorted;
}

static void
test_topo_sort(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t *sorted;

	printf("DIRECTED graph for the topological sort problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i)
	{
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
	}

	sorted = topo_sort(lg, visited);

	printf("Topologically sorted nodes:\n");
	ll_print_int(sorted);
	printf("\n");

	ll_free(&sorted);
	lg_free(lg);
}

static void
test_connected_comp(void)
{
	unsigned int num_comps, i, nodes, edges;
	int x, y;
	int visited[MAX_NODES] = {0};
	list_graph_t *lg;
	linked_list_t **comps;

	printf("UNDIRECTED graph for the connected components problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i)
	{
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	comps = connected_components(lg, visited, &num_comps);

	printf("Found %d connected components:\n", num_comps);
	for (i = 0; i != num_comps; ++i)
	{
		ll_print_int(comps[i]);
		ll_free(comps + i);
	}
	printf("\n");
	free(comps);
	lg_free(lg);
}

static void
test_min_dist(void)
{
	unsigned int i, nodes, edges;
	int x, y;
	int dist[MAX_NODES] = {0};
	list_graph_t *lg;

	printf("UNDIRECTED graph for the minimum distance problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i)
	{
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	for (i = 0; i != nodes; ++i)
		dist[i] = INF;

	min_path(lg, 0, dist);

	printf("Minimum distances to node 0:\n");
	for (i = 0; i != nodes; ++i)
		printf("%u: %d\n", i, dist[i]);
	printf("\n");

	lg_free(lg);
}

static void
test_bipartite(void)
{
	unsigned int i, nodes, edges;
	int color[MAX_NODES] = {0};
	int x, y;
	list_graph_t *lg;

	printf("UNDIRECTED graph for the bipartite graph problem:\n");
	scanf("%u %u", &nodes, &edges);
	lg = lg_create(nodes);

	for (i = 0; i != edges; ++i)
	{
		scanf("%d %d", &x, &y);
		lg_add_edge(lg, x, y);
		lg_add_edge(lg, y, x);
	}

	if (check_bipartite(lg, color))
	{
		printf("Nodes with colour 1:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 1)
				printf("%d ", i);
		printf("\nNodes with colour 2:\n");
		for (int i = 0; i < lg->nodes; ++i)
			if (color[i] == 2)
				printf("%d ", i);
		printf("\n");
	}
	else
		printf("The graph is not bipartite\n");

	lg_free(lg);
}

int main(void)
{
	/* Ex 1 */
	test_connected_comp();

	/* Ex 2 */
	test_topo_sort();

	/* Ex 3 */
	test_min_dist();

	/* Ex 4 */
	test_bipartite();

	return 0;
}

/*

UNDIRECTED graph for the connected components problem:
12 10 
0 1 
0 2 
1 2 
2 3 
4 5 
4 6 
5 6 
4 7 
7 8 
9 10 
Found 4 connected components:
0 2 3 1 
4 7 8 6 5 
9 10 
11 

DIRECTED graph for the topological sort problem:
6 7
2 5
2 0
5 0
4 0
1 4
3 0
3 1
Topologically sorted nodes:
3 2 5 1 4 0 

UNDIRECTED graph for the minimum distance problem:
7 10
0 1 
0 4 
1 2 
1 3 
1 4 
2 4 
3 5 
3 6 
4 5 
4 6 
0 6 0 4 1 6 5 2 3 Minimum distances to node 0:
0: 0
1: 1
2: 2
3: 2
4: 1
5: 2
6: 2

UNDIRECTED graph for the bipartite graph problem:
9 8 
0 1 
0 6 
1 2 
2 7 
3 6 
4 7 
4 8 
5 8 
0 Nodes with colour 1:
0 1 2 3 4 5 6 7 8 
Nodes with colour 2:


==296849== 
==296849== HEAP SUMMARY:
==296849==     in use at exit: 0 bytes in 0 blocks
==296849==   total heap usage: 56 allocs, 56 frees, 3,468 bytes allocated
==296849== 
==296849== All heap blocks were freed -- no leaks are possible
==296849== 
==296849== For lists of detected and suppressed errors, rerun with: -s
==296849== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

*/
