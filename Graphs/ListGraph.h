#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include "LinkedList.h"

typedef struct
{
	linked_list_t** neighbors; 
	int nodes;                 
} list_graph_t;

list_graph_t*
lg_create(int nodes);

void
lg_add_edge(list_graph_t* graph, int src, int dest);

int
lg_has_edge(list_graph_t* graph, int src, int dest);

linked_list_t*
lg_get_neighbours(list_graph_t* graph, int node);

void
lg_remove_edge(list_graph_t* graph, int src, int dest);

void
lg_free(list_graph_t* graph);

#endif /* LISTGRAPH_H_ */
