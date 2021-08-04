// Copyright 2021 Dinu Ion-Irinel

#include <stdio.h>
#include <stdlib.h>

#include "MatrixGraph.h"
#include "utils.h"

matrix_graph_t * mg_create(int node)
{
	matrix_graph_t *graph = malloc(sizeof(matrix_graph_t));
	DIE(graph == NULL, "Allocation Error\n");

	graph->nodes = nodes;

	graph->matrix = malloc(nodes * sizeof(int *));
	DIE(graph->matrix == NULL, "Alocation Error\n");
	for (int i = 0; i < nodes; ++i)
	{
		graph->matrix[i] = calloc(nodes, sizeof(int));
		DIE(graph->matrix[i] == NULL, "Allocation Error\n");
	}

	return graph;
}

void mg_add_edge(matrix_graph_t *graph, int src, int dest)
{
	if (graph == NULL)
	{
		return;
	}
	if (graph->nodes < src || graph->nodes < dest)
	{
		return;
	}

	graph->matrix[src][dest] = 1;
}

mg_has_edge(matrix_graph_t *graph, int src, int dest)
{
	if (graph == NULL || graph->matrix == NULL)
	{
		return -2;
	}
	if (graph->nodes < src || graph->nodes < dest)
	{
		return;
	}
	if (graph->matrix[src][dest] == 1)
	{
		return 1;
	}

	return 0;
}

void mg_remove_edge(matrix_graph_t *graph, int src, int dest)
{
	if (graph == NULL)
	{
		return;
	}
	if (graph->nodes < src || graph->nodes < dest)
	{
		return;
	}
	graph->matrix[src][dest] = 0;
}

void mg_free(matrix_graph_t *graph)
{
	if (graph == NULL)
	{
		return;
	}
	for (int i = 0; i < graph->nodes; ++i)
	{
		free(graph->matrix[i]);
	}
	free(graph->matrix);
	free(graph);
	return;
}