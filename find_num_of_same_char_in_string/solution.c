#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

///Node structure of binary tree
struct char_node_t {
    char data;
    uint8_t cnt;
    struct char_node_t *next;
};

typedef struct char_node_t node;

/**
 * Creates new node
 * @param[out] node
 */
static node *node_new_node(char data)
{
    node *tmp = (node *) malloc((sizeof(node)));
    tmp->next = NULL;
    tmp->data = data;
    tmp->cnt = 1;
    return tmp;
}

/**
 * Search all nodes
 * @param[in] node
 * @param[in] data
 * @param[out] boolen
 */
static bool node_search(node *root, char data)
{
    node *tmp = root;
    while (tmp != NULL) {
        if (tmp->data == data) {
            tmp->cnt++;
            printf("found same data:%c - cnt:%d\r\n", tmp->data, tmp->cnt);
            return true;
        }
        tmp = tmp->next;
    }
    return false;
}

/**
 * Checks all num of elements in root
 * @param[in] node
 * @param[out] boolen
 */
static bool node_cnt_compare(node *root)
{
    node *tmp = root;
    while (tmp != NULL) {
        if (tmp->next == NULL) {
            break;
        }
        printf("cnt comparing:%c (%d) with %c (%d)\r\n", tmp->data, tmp->cnt, tmp->next->data, tmp->next->cnt);
        if (tmp->cnt != tmp->next->cnt) {
            //printf(".\r\n");
            return false;
        }
        tmp = tmp->next;
    }
    return true;
}

/**
 * Inserts to nodes
 * @param[in] node
 * @param[out] node
 */
static node *node_insert_node(node *node, char data)
{
    if (node == NULL) {
        return node_new_node(data);
    }
    node->next = node_insert_node(node->next, data);
    return node;
}

bool is_valid(char *str)
{
    node *root = NULL;
    root = node_insert_node(root, '0');
    for (uint8_t s = 0; s < strlen(str); s++) {
        if (!node_search(root, str[s])) {
            node_insert_node(root, str[s]);
            //printf("%c \r\n", str[s]);
        }
    }

    return node_cnt_compare(root->next);
}
int main()
{
    if (is_valid("aabbccddeeffgg")) {
        printf("true");
    } else {
        printf("false");
    }
    return 0;
}
