#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"
#define DEBUG

/**
 * Creates new node
 * @param[out] node
 */

node *bin_tr_new_node(void)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->left_child = tmp->right_child = NULL;
    return tmp;
}

/**
 * Display the nodes
 * @param[in] root_node
 */
void bin_tr_print_node(node *root_node)
{
    if (root_node != NULL) {
        bin_tr_print_node(root_node->left_child);
#ifdef DEBUG
        printf("%p \n", (void *)&root_node);
#endif
        bin_tr_print_node(root_node->right_child);
    }
}

/**
 * Inserts to nodes
 * @param[in] node
 * @param[out] node
 */
node *bin_tr_insert_node(node *node)
{

    if (node == NULL) {
        return bin_tr_new_node();
    }
    if (rand() % 2) {
        node->left_child = bin_tr_insert_node(node->left_child);
    } else {
        node->right_child = bin_tr_insert_node(node->right_child);
    }
    return node;
}

/**
 * Checks same elements in root
 * @param[in] node
 * @param[out] boolen
 */
uint8_t bin_tr_is_anomaly(node *root_node)
{
    if (root_node == NULL) {
        return 0;
    }
#ifdef DEBUG
    printf("---------------\r\n");
    printf("root:%p \r\n", (void *)&root_node);
    if (root_node->left_child != NULL) {
        printf("root_left:%p \r\n", (void *)&root_node->left_child);
    }
    if (root_node->right_child != NULL) {
        printf("root_right:%p \r\n", (void *)&root_node->right_child);
    }
#endif
    if (root_node->left_child != NULL && (void *)&root_node->left_child == (void *)&root_node) {
        return 1;
    }
    if (root_node->right_child != NULL && (void *)&root_node->right_child == (void *)&root_node) {
        return 1;
    }
    if (root_node->left_child != NULL && root_node->right_child != NULL && (void *)&root_node->left_child == (void *)&root_node->right_child) {
        return 1;
    }
    if (bin_tr_is_anomaly(root_node->left_child) || bin_tr_is_anomaly(root_node->right_child)) {
        return 1;
    }
    return 0;
}
