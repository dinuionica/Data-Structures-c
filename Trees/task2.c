// Copyright 2021 Dinu Ion-Irinel

#include "binary_tree.h"

#define MAX(a,b) (((a)>(b))?(a):(b))

void read_tree(b_tree_t *b_tree)
{
    int i, N, data;

    scanf("%d\n", &N);

    for (i = 0; i < N; ++i) {
        scanf("%d ", &data);
        b_tree_insert(b_tree, &data);
    }
}

/* recursive function for finding a subtree with the maximum sum */
int find_sum_max_util(b_node_t *root, int *value) {

    if (root == NULL) {
        return 0;
    }
    
    /* we add to the current amount the value of the root and then we go through
     * recursively the left sub-tree and then the right one and we add
     * at the same amount the values of each node
     */
    int current_sum = *(int *)root->data + find_sum_max_util(root->left, value) 
                      + find_sum_max_util(root->right, value);

    *(int *)value = MAX(*(int *)value, current_sum);
    
    return current_sum;
}

int find_sum_max(b_node_t *root) {
    int value = 0;
    
    if (root == NULL) {
        return 0;
    }
    find_sum_max_util(root, &value);

    return value;
}
int main(void)
{
    b_tree_t *binary_tree;

    binary_tree = b_tree_create(sizeof(int));

    read_tree(binary_tree);

    printf("%d ", find_sum_max(binary_tree->root));

}

/* 
               1
            /    \
          -2      3
          / \    /  \
         4   5  -6   2


         -2
        /  \ 
       4    5
    sum_max = 4 + 5 - 2 = 7;

Output: 7


              1
            /   \
           2      3
          / \    / \
         4   5  6   7
    sum_max = 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28
    
Output: 28
*/

