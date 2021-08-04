// Copyright 2021 Dinu Ion Irinel

#include <stdlib.h>
#include <string.h>

#include "Queue.h"
#include "utils.h"

/* create queue */
queue_t *
q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *queue = malloc(sizeof(queue_t));
	DIE(queue == NULL, "Allocation Error\n");
	/* buffer allocation */
	queue->buff = malloc(max_size * sizeof(void *));
	DIE(queue->buff == NULL, "Allocation Error\n");

	queue->data_size = data_size;
	queue->max_size = max_size;
	queue->size = 0;
	queue->write_idx = -1;
	queue->read_idx = -1;

	return queue;
}
/* function to return calculat size of queue */
unsigned int
q_get_size(queue_t *q)
{
	if (q == NULL)
	{
		return -1;
	}
	return q->size;
}

/* function to check if the queue is empty  */
unsigned int
q_is_empty(queue_t *q)
{
	if (q == NULL)
	{
		return -1;
	}
	if (q_get_size(q) == 0)
	{
		return 1;
	}
	return 0;
}
/* return the top element*/
void *
q_front(queue_t *q)
{
	if (q == NULL)
	{
		return NULL;
	}
	return q->buff[q->read_idx];
}

/* 	Function to add a new element
 */
bool q_enqueue(queue_t *q, void *new_data)
{
	/* if queue is full return false */
	if (q_get_size(q) == q->max_size || q == NULL)
	{
		return false;
	}

	/* if queue is empty */
	if (q->read_idx == -1)
	{
		q->read_idx = 0;
		q->write_idx = 0;
		q->buff[q->write_idx] = malloc(q->data_size);
		DIE(q->buff[q->write_idx] == NULL, "Allocation Error\n");
		memcpy(q->buff[q->write_idx], new_data, q->data_size);
		q->size++;

		return true;
	}
	else
	{
		/* cicle */
		q->write_idx = (q->write_idx + 1) % q->max_size;
		q->buff[q->write_idx] = malloc(q->data_size);
		DIE(q->buff[q->write_idx] == NULL, "Allocation Error\n");
		memcpy(q->buff[q->write_idx], new_data, q->data_size);
		q->size++;
		return true;
	}
}

/*  function to remove a element from the queue
 */
bool q_dequeue(queue_t *q)
{
	if (q_is_empty(q) || q == NULL)
	{
		return false;
	}
	else if (q->read_idx == q->write_idx)
	{
		free(q->buff[q->read_idx]);
		q->buff[q->read_idx] = NULL;
		q->write_idx = -1;
		q->read_idx = -1;
		q->size--;
		return true;
	}
	else
	{
		free(q->buff[q->read_idx]);
		q->buff[q->read_idx] = NULL;
		q->read_idx = (q->read_idx + 1) % q->max_size;
		q->size--;
		return true;
	}
}

/* free buffer */
void q_clear(queue_t *q)
{
	if (q == NULL)
	{
		return;
	}
	while (q_get_size(q) > 0)
	{
		q_dequeue(q);
	}
}
/* distroy queue and free memory */
void q_free(queue_t *q)
{
	if (q == NULL)
	{
		return;
	}
	q_clear(q);
	free(q->buff);
	q->buff = NULL;
	free(q);
	q = NULL;
}
