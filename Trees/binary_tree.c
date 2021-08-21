/* Copyright 2021 Dinu Ion-Irinel */

#include "binary_tree.h"

#define MAX_NODES 100

/* the function that create a new node */
static b_node_t*
__b_node_create(void* data, size_t data_size)
{
    b_node_t* b_node;

    b_node = malloc(sizeof(*b_node));
    DIE(b_node == NULL, "b_node malloc");

    b_node->left = b_node->right = NULL;

    b_node->data = malloc(data_size);
    DIE(b_node->data == NULL, "b_node->data malloc");
    memcpy(b_node->data, data, data_size);

    return b_node;
}

/* the function that create a new bst */
b_tree_t*
b_tree_create(size_t data_size)
{
    b_tree_t *binary_tree = malloc(sizeof(b_tree_t));
    DIE(binary_tree ==  NULL, "binary_tree allocation\n");

    binary_tree->data_size = data_size;
    binary_tree->root = NULL;

    return binary_tree;
}

/* the function that add a new node */
void
b_tree_insert(b_tree_t* b_tree, void* data)
{
    queue_t* q;
    b_node_t *b_node, *b_node_tmp;

    b_node = __b_node_create(data, b_tree->data_size);

    if (!b_tree->root) {
        b_tree->root = b_node;
        return;
    }
    /* create queue and add the root */
    q = q_create(sizeof(void**), MAX_NODES);
    q_enqueue(q, &b_tree->root);
    while (!q_is_empty(q)) {
        b_node_tmp = *(b_node_t **)q_front(q);
        q_dequeue(q);

        /* if there is a left child I put it in the tail
         * and if it doesn't exist, I add it and stop the execution
         */
        if (b_node_tmp->left != NULL) {
            q_enqueue(q, &b_node_tmp->left);
        } else {
           b_node_tmp->left = b_node;
            q_free(q);
            return;
        }

       /* if there is a right child I put him in the queue
        * and if it doesn't exist, I add it and stop the execution
        */
        if (b_node_tmp->right != NULL) {
            q_enqueue(q, &b_node_tmp->right);
        } else {
            b_node_tmp->right = b_node;
            q_free(q);
            return;
        }
    }
}

/* function for pre-traversing of bst */
static void
__b_tree_print_preorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;
    /* root, left, right */
    printf("%d ", *(int *)b_node->data);
    __b_tree_print_preorder(b_node->left, print_data);
    __b_tree_print_preorder(b_node->right, print_data);
}

void
b_tree_print_preorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_preorder(b_tree->root, print_data);
    printf("\n");
}

/* function for in-traversing of bst */
static void
__b_tree_print_inorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;
    /* left, root, right*/
    __b_tree_print_inorder(b_node->left, print_data);
    printf("%d ", *(int *)b_node->data);
    __b_tree_print_inorder(b_node->right, print_data);
}

void
b_tree_print_inorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_inorder(b_tree->root, print_data);
    printf("\n");
}
/* function for preorder-traversing of bst */
static void
__b_tree_print_postorder(b_node_t* b_node, void (*print_data)(void*))
{
    if (!b_node)
        return;
    /* left, right, root  */
    __b_tree_print_postorder(b_node->left, print_data);
    __b_tree_print_postorder(b_node->right, print_data);
    printf("%d ", *(int *)b_node->data);
}

void
b_tree_print_postorder(b_tree_t* b_tree, void (*print_data)(void*))
{
    __b_tree_print_postorder(b_tree->root, print_data);
    printf("\n");
}

/*the function that remove memory allocated recursivly */
static void
__b_tree_free(b_node_t* b_node, void (*free_data)(void*))
{
    if (!b_node)
        return;
    
    __b_tree_free(b_node->left, free_data);
    __b_tree_free(b_node->right, free_data);
    free(b_node->data);
    b_node->data = NULL;
    free(b_node);
    b_node = NULL;
}

void
b_tree_free(b_tree_t* b_tree, void (*free_data)(void*))
{
    __b_tree_free(b_tree->root, free_data);
    free(b_tree);
}

b_node_t *find_bottom_left(b_node_t *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

/* bonus implementation */
void my_free(b_tree_t *b_tree) {

    b_node_t *node = b_tree->root;
    if (node == NULL) {
        return;
    }
    /* find left-child */
    b_node_t *bottom_left_node = find_bottom_left(node);
    while (node != NULL) {
        if (node->right != NULL) {
            /* change pointers */
            bottom_left_node->left = node->right;
            bottom_left_node = find_bottom_left(bottom_left_node);
        }
        /* free node and redirect to NULL */
        b_node_t *temp = node;
        node = node->left;
        free(temp->data);
        temp->data = NULL;
        free(temp);
        temp = NULL;
    }

    free(b_tree);
    b_tree = NULL;
}
