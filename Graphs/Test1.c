// Copyright 2021 Dinu Ion-Irinel
#include <stdio.h>
#include <stdlib.h>

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "Queue.h"
#include "Stack.h"
#include "utils.h"

#define MAX_NODES 10

enum color
{
	WHITE,
	GRAY,
	BLACK
};

// the function for designing the adjacent matrix
void print_matrix_graph(matrix_graph_t *mg)
{
	if (mg == NULL)
	{
		return;
	}
	for (int i = 0; i < mg->nodes; ++i)
	{
		for (int j = 0; j < mg->nodes; ++j)
		{
			printf("%d ", mg->matrix[i][j]);
		}
		printf("\n");
	}
}

// the function for printing the list of the graph
void print_list_graph(list_graph_t *lg)
{
	if (lg == NULL)
	{
		return;
	}
	for (int i = 0; i < lg->nodes; ++i)
	{
		ll_node_t *current = lg->neighbors[i]->head;
		while (current != NULL)
		{
			printf("---> %d", *(int *)current->data);
			current = current->next;
		}
	}
}

// dfs iterative dfs for implementing the graph using lists
void dfs_list_graph(list_graph_t *lg,
					int node,
					int *visited)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		visited[i] = WHITE;
	}
	// create the stack
	stack_t *stack = st_create(sizeof(int));
	// add first node and mark it
	visited[node] = GRAY;
	printf("%d ", node);
	st_push(stack, &node);

	while (!st_is_empty(stack))
	{
		// take the top of the stack
		int top = *(int *)st_peek(stack);
		int node_found = 0;
		int v = 0;
		ll_node_t *node = lg->neighbors[top]->head;
		// find unvisited neighbours
		while (node != NULL && node_found == 0)
		{
			v = *(int *)node->data;
			if (visited[v] == WHITE)
			{
				node_found = 1;
			}
			else
			{
				node = node->next;
			}
		}
		// if I found a neighbor I add it to the stack and mark it
		if (node_found == 1)
		{
			visited[v] = GRAY;
			printf("%d ", v);
			st_push(stack, &v);
		}
		else
		{
			// if I don't make it black and remove it
			visited[top] = BLACK;
			st_pop(stack);
		}
	}
	// free memory
	st_clear(stack);
	st_free(stack);
}
// dfs recursive dfs for graph implementation using the adjacency matrix
int dfs_matrix_graph(matrix_graph_t *mg,
					 int node,
					 int *visited)
{
	enum color;
	if (mg == NULL)
	{
		return;
	}
	// print first node and mark it
	printf("%d ", node);
	visited[node] = GRAY;
	// I look for the first unvisited neighbor and call the function again
	for (int i = 0; i < mg->nodes; ++i)
	{
		if (mg->matrix[node][i] == 1 && visited[i] == WHITE)
		{
			dfs_matrix_graph(mg, i, visited);
		}
	}
}

// bfs iterative for graph implementation using lists
void bfs_list_graph(list_graph_t *lg, int node, int *color, int *parent)
{
	enum color;
	if (lg == NULL)
	{
		return;
	}
	// initialization
	for (int i = 0; i < lg->nodes; ++i)
	{
		color[i] = WHITE;
		parent[i] = -1;
	}

	queue_t *queue = q_create(sizeof(int), MAX_NODES);
	// add the first node
	printf("%d ", node);
	q_enqueue(queue, &node);
	parent[node] = -1;
	color[node] = GRAY;

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
			// if I find an unvisited one I add it in the queue
			if (color[v] == WHITE)
			{
				printf("%d ", v);
				color[v] = GRAY;
				parent[v] = top;
				q_enqueue(queue, &v);
			}
			current = current->next;
		}
		// mark the node
		color[top] = BLACK;
	}
	// free memory
	q_clear(queue);
	q_free(queue);
}

// iterative bfs for implementing the adjacent matrix graph
void bfs_matrix_graph(matrix_graph_t *mg, int node, int *color, int *parent)
{
	if (mg == NULL)
	{
		return;
	}
	// initialization
	for (int i = 0; i < mg->nodes; ++i)
	{
		color[i] = WHITE;
		parent[i] = -1;
	}

	queue_t *queue = q_create(sizeof(int), MAX_NODES);
	// add the first node in queue
	printf("%d ", node);
	q_enqueue(queue, &node);
	color[node] = GRAY;
	parent[node] = -1;

	while (!q_is_empty(queue))
	{
		// remove the first element from the queue and display it
		int top = *(int *)q_front(queue);
		printf("%d ", top);
		q_dequeue(queue);

		/* I'm looking for the neighbors of the node and if I find one
		   which is unvisited I add it in the queue */
		for (int i = 0; i < mg->nodes; ++i)
		{
			if (mg->matrix[top][i] == 1 && color[i] == 1)
			{
				color[i] = GRAY;
				parent[i] = top;
				q_enqueue(queue, &i);
			}
		}
		// mark the node
		color[top] = BLACK;
	}
	// free memory
	q_clear(queue);
	q_free(queue);
}

// floyd-warshall algorihm
void floyd_warshall(matrix_graph_t *mg)
{
	// create distance matrix
	int matrix[MAX_NODES][MAX_NODES];

	// copy matrix
	for (int i = 0; i < MAX_NODES; ++i)
	{
		for (int j = 0; j < MAX_NODES; ++j)
		{
			matrix[i][j] = mg->matrix[i][j];
		}
	}

	// find all nodes
	for (int k = 0; k < mg->nodes; ++k)
	{
		for (int i = 0; i < mg->nodes; ++i)
		{
			for (int j = 0; j < mg->nodes; ++j)
			{

				// if k is on the shortest path from i to j
				if (matrix[i][k] + matrix[k][j] < matrix[i][j])
				{
					matrix[i][j] = matrix[i][k] + matrix[k][j];
				}
			}
		}
	}

	//  display matrix
	for (int i = 0; i < MAX_NODES; ++i)
	{
		for (int j = 0; j < MAX_NODES; ++j)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int nodes, edges;
	int x[MAX_NODES], y[MAX_NODES];
	int visited[MAX_NODES], t_dest[MAX_NODES], t_fin[MAX_NODES];
	list_graph_t *lg = lg_create(MAX_NODES);
	matrix_graph_t *mg = mg_create(MAX_NODES);

	int numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	printf("-------------------------------- Test ListGraph "
		   "--------------------------------\n");
	/* Test add_edge_list_graph has_edge_list_graph */

	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		   lg_has_edge(lg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		   lg_has_edge(lg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		   lg_has_edge(lg, numbers[2], numbers[4]));

	/* Test remove_edge_list_graph */
	lg_remove_edge(lg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		   lg_has_edge(lg, numbers[0], numbers[1]));

	/* Test get_neighbours_list_graph */
	lg_add_edge(lg, numbers[0], numbers[1]);
	lg_add_edge(lg, numbers[0], numbers[2]);
	lg_add_edge(lg, numbers[0], numbers[3]);
	lg_add_edge(lg, numbers[0], numbers[4]);

	linked_list_t *l = lg_get_neighbours(lg, numbers[0]);

	printf("#5:\n");
	printf("Output: ");
	ll_print_int(l);
	printf("Output asteptat: 1 2 3 4\n");

	printf("-------------------------------- Test MatrixGraph "
		   "--------------------------------\n");
	/* test add edge_matrix_graph has_edge_matrix_graph */
	mg_add_edge(mg, numbers[0], numbers[1]);
	mg_add_edge(mg, numbers[3], numbers[2]);

	printf("#1:\nOutput: %d\nOutput asteptat: 1\n",
		   mg_has_edge(mg, numbers[0], numbers[1]));

	printf("#2:\nOutput: %d\nOutput asteptat: 1\n",
		   mg_has_edge(mg, numbers[3], numbers[2]));

	printf("#3:\nOutput: %d\nOutput asteptat: 0\n",
		   mg_has_edge(mg, numbers[2], numbers[4]));

	/* test remove_edge_matrix_graph */
	mg_remove_edge(mg, numbers[0], numbers[1]);
	printf("#4:\nOutput: %d\nOutput asteptat: 0\n",
		   mg_has_edge(mg, numbers[0], numbers[1]));

	lg_free(lg);
	mg_free(mg);

	matrix_graph_t *mg2 = mg_create(MAX_NODES);

	mg_add_edge(mg2, 0, 1);
	mg_add_edge(mg2, 0, 2);
	mg_add_edge(mg2, 0, 3);
	mg_add_edge(mg2, 0, 4);

	int *array_visited = calloc(MAX_NODES, sizeof(int));
	DIE(array_visited == NULL, "Error of malloc\n");
	dfs_matrix_graph(mg2, 0, array_visited);
	mg_free(mg2);
	free(array_visited);
	printf("\n");

	// test bfs for list
	list_graph_t *lg2 = lg_create(MAX_NODES);

	lg_add_edge(lg2, 0, 1);
	lg_add_edge(lg2, 0, 2);
	lg_add_edge(lg2, 1, 3);
	lg_add_edge(lg2, 1, 4);
	lg_add_edge(lg2, 2, 5);
	lg_add_edge(lg2, 2, 6);

	bfs_list_graph(lg2, 0, x, y);

	lg_free(lg2);
	return 0;
}

/*
-------------------------------- Test ListGraph --------------------------------
#1:
Output: 1
Output asteptat: 1
#2:
Output: 1
Output asteptat: 1
#3:
Output: 0
Output asteptat: 0
#4:
Output: 0
Output asteptat: 0
#5:
Output: 1 2 3 4 
Output asteptat: 1 2 3 4
-------------------------------- Test MatrixGraph --------------------------------
#1:
Output: 1
Output asteptat: 1
#2:
Output: 1
Output asteptat: 1
#3:
Output: 0
Output asteptat: 0
#4:
Output: 0
Output asteptat: 0

0 1 2 3 4 

0 1 2 3 4 5 6

==427646== HEAP SUMMARY:
==427646==     in use at exit: 0 bytes in 0 blocks
==427646==   total heap usage: 83 allocs, 83 frees, 2,948 bytes allocated
==427646== 
==427646== All heap blocks were freed -- no leaks are possible
==427646== 
==427646== For lists of detected and suppressed errors, rerun with: -s
==427646== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
dinuionica@ubuntu:~/Documents/University/SD/Labs/315caa-dinuionirinel8/lab/0

 */