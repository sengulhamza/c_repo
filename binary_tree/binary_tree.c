#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG

///Node structure of binary tree
struct node_t {
    struct node_t *left_child;
    struct node_t *right_child;
};

typedef struct node_t node;

/**
 * Creates new node
 * @param[out] node
 */

static node *new_node(void)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->left_child = tmp->right_child = NULL;
    return tmp;
}

/**
 * Display the nodes
 * @param[in] root_node
 */
static void print_node(node *root_node)
{
    if (root_node != NULL) {
        print_node(root_node->left_child);
#ifdef DEBUG
        printf("%p \n", (void *)&root_node);
#endif
        print_node(root_node->right_child);
    }
}

/**
 * Inserts to nodes
 * @param[in] node
 * @param[out] node
 */
static node *insert_node(node *node)
{

    if (node == NULL) {
        return new_node();
    }
    if (rand() % 2) {
        node->left_child = insert_node(node->left_child);
    } else {
        node->right_child = insert_node(node->right_child);
    }
    return node;
}

/**
 * Checks same elements in root
 * @param[in] node
 * @param[out] boolen
 */
static bool is_anomaly(node *root_node)
{
    if (root_node == NULL) {
        return false;
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
        return true;
    }
    if (root_node->right_child != NULL && (void *)&root_node->right_child == (void *)&root_node) {
        return true;
    }
    if (root_node->left_child != NULL && root_node->right_child != NULL && (void *)&root_node->left_child == (void *)&root_node->right_child) {
        return true;
    }
    if (is_anomaly(root_node->left_child) || is_anomaly(root_node->right_child)) {
        return true;
    }
    return false;
}

int main()
{
    node *root_node = NULL;
    root_node = insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);
    insert_node(root_node);


    print_node(root_node);

    if (is_anomaly(root_node)) {
        printf("There is anomaly \n");
    } else {
        printf("There is not anomaly \n");
    }
    return 0;
}
