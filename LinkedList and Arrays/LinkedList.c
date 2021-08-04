// Copyright 2021 Dinu Ion Irinel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utils.h"

// function to create a linkedlist
linked_list_t *
ll_create(unsigned int data_size)
{
    linked_list_t *list = malloc(sizeof(linked_list_t));
    DIE(list == NULL, "Error of malloc\n");

    list->data_size = data_size;
    list->head = NULL;
    list->size = 0;

    return list;
}

// function to add a new node in list
void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data)
{
    if (n < 0)
    {

        printf("Error!\n");
        return;
    }
    else if (n == 0)
    {

        ll_node_t *new = malloc(sizeof(ll_node_t));
        DIE(new == NULL, "Error of malloc\n");

        ll_node_t *current = NULL;

        new->data = malloc(sizeof(list->data_size) + 1);
        memcpy(new->data, new_data, sizeof(list->data_size) + 1);
        new->next = NULL;
        current = list->head;
        list->head = new;
        new->next = current;
        list->size++;
    }
    else if (n >= list->size)
    {

        ll_node_t *new = malloc(sizeof(ll_node_t));
        DIE(new == NULL, "Error of malloc\n");

        ll_node_t *current = NULL;

        new->data = malloc(sizeof(list->data_size) + 1);
        memcpy(new->data, new_data, sizeof(list->data_size) + 1);
        new->next = NULL;

        if (list->head == NULL)
        {

            list->head = new;
            list->size++;
        }
        else
        {

            current = list->head;
            while (current->next != NULL)
            {
                current = current->next;
            }

            current->next = new;
            list->size++;
        }
    }
    else
    {

        ll_node_t *current = NULL;

        int count = 0;
        current = list->head;

        while (count != (int)n - 1)
        {
            current = current->next;
            count++;
        }

        ll_node_t *new = malloc(sizeof(ll_node_t));
        DIE(new == NULL, "Error of malloc\n");

        new->data = malloc(sizeof(list->data_size) + 1);
        memcpy(new->data, new_data, sizeof(list->data_size) + 1);
        new->next = current->next;
        current->next = new;
        list->size++;
    }
}

// function to remove a node from list
ll_node_t *
ll_remove_nth_node(linked_list_t *list, unsigned int n)
{
    if (n < 0)
    {
        printf("Error\n");
        return NULL;
    }
    else if (n == 0)
    {

        ll_node_t *first_node = malloc(sizeof(ll_node_t));
        DIE(first_node == NULL, "Error of malloc\n");
        first_node = list->head;
        list->head = first_node->next;
        list->size--;
        return first_node;
    }
    else
    {

        ll_node_t *current = NULL, *previous = NULL;

        current = list->head;
        int index = 0;
        while (current != NULL)
        {
            if (index == (int)n)
            {
                previous->next = current->next;
                return current;
            }
            index++;
            previous = current;
            current = current->next;
            list->size--;
        }
    }
}

// function to return size of the list
unsigned int
ll_get_size(linked_list_t *list)
{
    return list->size;
}

// function to free all memory
void ll_free(linked_list_t **pp_list)
{
    linked_list_t *list = *pp_list;
    ll_node_t *temp = NULL, *current = NULL;
    current = list->head;

    while (current != NULL)
    {

        temp = current;
        current = current->next;
        free(temp->data);
        free(temp);
    }

    free(list);
    list = NULL;
}

// function to print integers elements of the list
void ll_print_int(linked_list_t *list)
{
    ll_node_t *current = list->head;

    while (current != NULL)
    {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }

    printf("\n");
}

// function to print string elements of the list
void ll_print_string(linked_list_t *list)
{
    ll_node_t *current = list->head;

    while (current != NULL)
    {
        printf("%s ", (char *)current->data);
        current = current->next;
    }

    printf("\n");
}
