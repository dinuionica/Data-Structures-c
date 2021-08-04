// Copyright 2021 Dinu Ion Irinel

#include <stdlib.h>

#include "Stack.h"
#include "utils.h"

/* create stack */
stack_t *
st_create(unsigned int data_size)
{
	stack_t *stack = malloc(sizeof(stack_t));
	DIE(stack == NULL, "Allocation Error\n");

	stack->list = ll_create(data_size);

	return stack;
}
/* get size of the stack */
unsigned int
st_get_size(stack_t *st)
{
	if (st == NULL)
	{
		return -1;
	}
	return ll_get_size(st->list);
}

/* check if the stack is empty */
unsigned int
st_is_empty(stack_t *st)
{
	if (st == NULL)
	{
		return -1;
	}
	if (st_get_size(st) > 0)
	{
		return 0;
	}
	return 1;
}

/* get first element of stack */
void *
st_peek(stack_t *st)
{
	if (st == NULL)
	{
		return NULL;
	}

	ll_node_t *top = (st->list)->head->data;
	return (void *)top;
}

/* get and remove first element of the stack */
void st_pop(stack_t *st)
{
	if (st == NULL)
	{
		return;
	}

	ll_node_t *remove = ll_remove_nth_node(st->list, 0);
	free(remove->data);
	free(remove);
}

/* add a new element at the top of the stack */
void st_push(stack_t *st, void *new_data)
{
	if (st == NULL)
	{
		return;
	}
	ll_add_nth_node(st->list, 0, new_data);
}

/* clear stack */
void st_clear(stack_t *st)
{
	if (st == NULL)
	{
		return;
	}
	while (ll_get_size(st->list) > 0)
	{
		st_pop(st);
	}
}
/* destroy the stack */
void st_free(stack_t *st)
{
	if (st == NULL)
	{
		return;
	}

	free(st->list);
	free(st);
	st = NULL;
}
