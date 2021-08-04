// Copyright 2021 Dinu Ion Irinel

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#include "Hashtable.h"

#define MAX_BUCKET_SIZE 64

// function to compare integers
int compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b)
	{
		return 0;
	}
	else if (int_a < int_b)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

// function to compare strings
int compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

// hash function
unsigned int
hash_function_int(void *a)
{
	// Credits: https://stackoverflow.com/a/12996028/7883884

	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	unsigned char *puchar_a = (unsigned char *)a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

// function to create a hashtable
hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void *),
		  int (*compare_function)(void *, void *))
{

	hashtable_t *ht = malloc(sizeof(hashtable_t));
	DIE(ht == NULL, "Error of malloc\n");

	ht->hmax = hmax;
	ht->size = 1;
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;

	ht->buckets = malloc(hmax * sizeof(linked_list_t *));
	DIE(ht->buckets == NULL, "Error of malloc\n");
	for (int i = 0; i < hmax; ++i)
	{
		ht->buckets[i] = ll_create(sizeof(struct info));
	}
	return ht;
}

// function to add a new key with value in hashtable
void ht_put(hashtable_t *ht, void *key, unsigned int key_size,
			void *value, unsigned int value_size)
{
	long i = ht->hash_function(key) % ht->hmax;
	int pos = 0;

	ll_node_t *current = (ht->buckets[i])->head;

	while (current != NULL)
	{
		struct info *info = current->data;
		if (ht->compare_function(info->key, key) == 0)
		{
			memcpy(info->value, value, value_size);
			return;
		}
		current = current->next;
		pos = pos + 1;
	}

	struct info *new_info = malloc(sizeof(struct info));
	DIE(new_info == NULL, "Error of malloc\n");

	new_info->key = malloc(key_size);
	DIE(new_info->key == NULL, "Error of malloc\n");
	memcpy(new_info->key, key, key_size);

	new_info->value = malloc(value_size);
	DIE(new_info->value == NULL, "Error of malloc\n");
	memcpy(new_info->value, value, value_size);

	ll_add_nth_node(ht->buckets[i], pos, new_info);
}

// function to get a value from hastable
void *
ht_get(hashtable_t *ht, void *key)
{
	int i = ht->hash_function(key) % ht->hmax;

	ll_node_t *current = (ht->buckets[i])->head;

	while (current != NULL)
	{
		struct info *info = current->data;
		if (ht->compare_function(info->key, key) == 0)
		{
			return info->value;
		}
		current = current->next;
	}
	return NULL;
}

// function to check if the hastable contain a key
int ht_has_key(hashtable_t *ht, void *key)
{
	int i = ht->hash_function(key) % ht->hmax;

	ll_node_t *current = (ht->buckets[i])->head;

	while (current != NULL)
	{
		struct info *info = current->data;
		if (ht->compare_function(info->key, key) == 0)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}

// function to remove a key with value
void ht_remove_entry(hashtable_t *ht, void *key)
{
	int i = ht->hash_function(key) % ht->hmax;
	ll_node_t *current = (ht->buckets[i])->head;
	int pos = 0;

	while (current != NULL)
	{
		struct info *info = current->data;
		if (ht->compare_function(info->key, key) == 0)
		{
			free(info->key);
			free(info->value);
			ll_remove_nth_node(ht->buckets[i], pos);
		}
		pos++;
		current = current->next;
	}
}

// function to free all the memory
void ht_free(hashtable_t *ht)
{
	for (int i = 0; i < ht->hmax; ++i)
	{

		ll_node_t *node = ht->buckets[i]->head;
		while (node != NULL)
		{
			ll_node_t *prev = node;
			node = node->next;
			struct info *info = prev->data;
			free(info->key);
			free(info->value);
			free(prev->data);
			free(prev);
		}
		free(ht->buckets[i]);
	}
	free(ht->buckets);
	free(ht);
	ht = NULL;
}
// function to get the size of the hashtable
unsigned int
ht_get_size(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->size;
}
// function to get the maximum size of the hashtable
unsigned int
ht_get_hmax(hashtable_t *ht)
{
	if (ht == NULL)
		return 0;

	return ht->hmax;
}
