/* Copyrighy 2021 Dinu Ion-Irinel */

#include "bst.h"
#include "utils.h"

/**
 * Helper function to create a node
 * @data: the data to be added in the node
 * @data_size: data's size
 */
static bst_node_t *__bst_node_create(void *data, size_t data_size)
{
    bst_node_t *bst_node;

    bst_node = malloc(sizeof(*bst_node));

    DIE(bst_node == NULL, "bst_node malloc");

    bst_node->left = bst_node->right = NULL;

    bst_node->data = malloc(data_size);
    DIE(bst_node->data == NULL, "bst_node->data malloc");
    memcpy(bst_node->data, data, data_size);

    return bst_node;
}

bst_tree_t *bst_tree_create(size_t data_size,
                            int (*cmp_f)(const void *, const void *))
{
    bst_tree_t *bst_tree;

    bst_tree = malloc(sizeof(*bst_tree));
    DIE(bst_tree == NULL, "bst_tree malloc");

    bst_tree->root = NULL;
    bst_tree->data_size = data_size;
    bst_tree->cmp = cmp_f;

    return bst_tree;
}

static void __bst_insert (bst_node_t ** root, void * value, int (* cmp_f) (const void *, const void *), size_t data_size)
{

     if ((* root) == NULL)
     {
         (* root) = __bst_node_create (value, data_size);
         return;
     }
     // if the value is higher I go on the subtree as recursive
     if (cmp_f ((* root) -> data, value) <0)
     {
         __bst_insert (& ((* root) -> right), value, cmp_f, data_size);
     }
     else
     {
         // if the value is lower I go on the left recursive subtree
         __bst_insert (& ((* root) -> left), value, cmp_f, data_size);
     }
}

void bst_tree_insert (bst_tree_t * bst_tree, void * data)
{
     // if the bst is empty
     if (bst_tree-> root == NULL)
     {
         bst_tree-> root = __bst_node_create (data, bst_tree-> data_size);
         return;
     }
     else
     {
         // if not, go through the subtree recursively
         __bst_insert (& bst_tree-> root, data, bst_tree-> cmp, bst_tree-> data_size);
     }
}
static bst_node_t *find_max(bst_node_t *node)
{

    bst_node_t *current = node;

    while (current != NULL && current->right != NULL)
    {
        current = current->right;
    }
    return current;
}
/**
 * Helper function to remove an element from a BST
 * @bst_node: the binary search subtree's root where to remove the element from
 * @data: the data that is contained by the node which has to be removed
 * @data_size: data size
 * @cmp: function used to compare the data contained by two nodes
 */
static bst_node_t * __ bst_tree_remove (bst_node_t * bst_node,
                                     void * data, size_t data_size,
                                     int (* cmp) (const void *, const void *))
{
    int rc;

    if (! bst_node)
        return NULL;

    rc = cmp (data, bst_node-> data);

    if (rc <0)
    {
        // I'm looking in the left subtree
        __bst_tree_remove (bst_node-> left, data, data_size, cmp);
    }
    else if (rc> 0)
    {
        // I'm looking in the right subtree
        __bst_tree_remove (bst_node-> right, data, data_size, cmp);
    }
    else
    {
        // if it is the leaf
        if (bst_node-> left == NULL && bst_node-> right == NULL)
        {
            free (bst_node-> data);
            free (bst_node);
            bst_node = NULL;
        }
        else
        {
            // is not the leaf
            // has only left subtree
            if (bst_node-> right == NULL)
            {
                bst_node_t * temp = bst_node;
                bst_node = bst_node-> left;
                free (temp-> data);
                free (temp);
            }
            // has only straight subtree
            if (bst_node-> left == NULL)
            {
                bst_node_t * temp = bst_node;
                bst_node = bst_node-> right;
                free (temp-> data);
                free (temp);
            }
            else
            {
                // if he has two children
                // I'm looking for the maximum in the right subtree
                bst_node_t * temp = find_max (bst_node-> left);
                bst_node-> data = temp-> data;

                bst_node-> left = __bst_tree_remove (bst_node-> left, temp-> data, data_size, cmp);
            }
        }
    }

    return bst_node;
}
void bst_tree_remove(bst_tree_t *bst_tree, void *data)
{
    bst_tree->root = __bst_tree_remove(bst_tree->root, data,
                                       bst_tree->data_size, bst_tree->cmp);
}

/**
 * Free the left and the right subtree of a node, its data and itself
 * @b_node: the node which has to free its children and itself
 * @free_data: function used to free the data contained by a node
 */
static void __bst_tree_free (bst_node_t * bst_node, void (* free_data) (void *))
{
     if (! bst_node)
         return;
     // free up memory for the left subtree
     __bst_tree_free (bst_node-> left, free_data);
     // free up memory for the right subtree
     __bst_tree_free (bst_node-> right, free_data);
     free (bst_node-> data);
     bst_node-> data = NULL;
     free (bst_node);
     bst_node = NULL;
}

void bst_tree_free(bst_tree_t *bst_tree, void (*free_data)(void *))
{
    __bst_tree_free(bst_tree->root, free_data);
    free(bst_tree);
}

static void
__bst_tree_print_inorder(bst_node_t *bst_node, void (*print_data)(void *))
{
    if (!bst_node)
        return;

    __bst_tree_print_inorder(bst_node->left, print_data);
    print_data(bst_node->data);
    __bst_tree_print_inorder(bst_node->right, print_data);
}

void bst_tree_print_inorder(bst_tree_t *bst_tree, void (*print_data)(void *))
{
    __bst_tree_print_inorder(bst_tree->root, print_data);
}
