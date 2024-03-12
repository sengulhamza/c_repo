#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#include <stdint.h>

///Node structure of binary tree
struct node_t {
    struct node_t *left_child;
    struct node_t *right_child;
};

typedef struct node_t node;

#ifdef __cplusplus
extern "C" {
#endif

node *bin_tr_new_node(void);
void bin_tr_print_node(node *root_node);
node *bin_tr_insert_node(node *node);
uint8_t bin_tr_is_anomaly(node *root_node);

#ifdef __cplusplus
}
#endif

#endif