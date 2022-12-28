#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "hex_dump.h"
#include "binary_tree.h"

int main()
{
    node *root_node = NULL;
    root_node = bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);
    bin_tr_insert_node(root_node);

    bin_tr_print_node(root_node);

    if (bin_tr_is_anomaly(root_node)) {
        printf("There is anomaly \n");
    } else {
        printf("There is not anomaly \n");
    }
    hex_dump(VARIABLE_PTR_STRGFY((uint8_t *) root_node), sizeof(root_node));
    return 0;
}